//
// Created by Swaraj Pradhan on 03/04/26.
//

#ifndef MOVEGEN_H
#define MOVEGEN_H
#include <functional>

#include "movegen/attacks.h"
#include "position/move.h"
#include "movegen/movelist.h"
#include "position/position.h"

class movegen {
public:
    virtual ~movegen() = default;

    virtual MoveList allMoves(Board* b) = 0;
    virtual MoveList capturesOnly(Board* b) = 0;
    virtual bool isLegal(Board* b, Move m) = 0;
protected:
    static MoveList knightMoves(Square from, uint64_t friendly, uint64_t enemy);
    static MoveList bishopMoves(Square from, uint64_t friendly, uint64_t enemy);
    static MoveList rookMoves(Square from, uint64_t friendly, uint64_t enemy);
    static MoveList queenMoves(Square from, uint64_t friendly, uint64_t enemy);
    static MoveList kingMoves(Square from, uint64_t friendly, uint64_t enemy);
    static MoveList pawnMoves(Square from, uint64_t friendly, uint64_t enemy, Color side);
    static MoveList chessmanMoves(Chessman cm, Square from, uint64_t friendly, uint64_t enemy, Color side);
    static bool isKingInCheck(Board* b, Color c);
};

inline MoveList movegen::knightMoves(Square from, uint64_t friendly, uint64_t enemy) {
    uint8_t rank = rank_of(from), file = file_of(from);
    auto occupied = [&](uint64_t pos, Square sq) -> bool {
        uint64_t bitsq = 1ULL<<sq;
        return pos&bitsq;
    };
    MoveList ml;
    Square to;
    if ((to = make_square(rank+2, file-1)) != NO_SQUARE && !occupied(friendly, to)) ml.add(Move(from, to));
    if ((to = make_square(rank+2, file+1)) != NO_SQUARE && !occupied(friendly, to)) ml.add(Move(from, to));
    if ((to = make_square(rank+1, file+2)) != NO_SQUARE && !occupied(friendly, to)) ml.add(Move(from, to));
    if ((to = make_square(rank+1, file-2)) != NO_SQUARE && !occupied(friendly, to)) ml.add(Move(from, to));
    if ((to = make_square(rank-1, file+2)) != NO_SQUARE && !occupied(friendly, to)) ml.add(Move(from, to));
    if ((to = make_square(rank-1, file-2)) != NO_SQUARE && !occupied(friendly, to)) ml.add(Move(from, to));
    if ((to = make_square(rank-2, file+1)) != NO_SQUARE && !occupied(friendly, to)) ml.add(Move(from, to));
    if ((to = make_square(rank-2, file-1)) != NO_SQUARE && !occupied(friendly, to)) ml.add(Move(from, to));

    return ml;
}


inline MoveList movegen::bishopMoves(Square from, uint64_t friendly, uint64_t enemy) {
    uint8_t rank = rank_of(from), file = file_of(from);
    auto occupied = [&](uint64_t pos, Square sq) -> bool {
        uint64_t bitsq = 1ULL<<sq;
        return pos&bitsq;
    };
    MoveList ml;
    Square to;
    int dir[4][2]= {{1,1}, {1, -1}, {-1, 1}, {-1,-1}};
    for (const auto &d: dir) {
        for (int i=1;i<8;i++) {
            if ((to = make_square(rank+i, file+i)) == NO_SQUARE
                || occupied(friendly, to)) break;
            ml.add(Move(from, to));
            if (occupied(enemy, to)) break;
        }
    }

    return ml;
}

inline MoveList movegen::rookMoves(Square from, uint64_t friendly, uint64_t enemy) {
    uint8_t rank = rank_of(from), file = file_of(from);
    auto occupied = [&](uint64_t pos, Square sq) -> bool {
        uint64_t bitsq = 1ULL<<sq;
        return pos&bitsq;
    };
    MoveList ml;
    Square to;
    int dir[4][2]= {{0, 1}, {0, -1}, {1, 0}, {-1,0}};
    for (const auto &d: dir) {
        for (int i=1;i<8;i++) {
            if ((to = make_square(rank+i, file+i)) == NO_SQUARE
                || occupied(friendly, to)) break;
            ml.add(Move(from, to));
            if (occupied(enemy, to)) break;
        }
    }
    return ml;
}

inline MoveList movegen::queenMoves(Square sq,  uint64_t friendly, uint64_t enemy) {
    MoveList mlrook = rookMoves(sq, friendly, enemy);
    MoveList mlbishop = bishopMoves(sq, friendly, enemy);

    for (int i=0;i<mlbishop.count;i++) mlrook.add(mlbishop[i]);

    return mlrook;
}

inline MoveList movegen::kingMoves(Square from, uint64_t friendly, uint64_t enemy) {
    uint8_t rank = rank_of(from), file = file_of(from);
    MoveList ml;
    auto occupied = [&](uint64_t pos, Square sq) -> bool {
        uint64_t bitsq = 1ULL<<sq;
        return pos&bitsq;
    };
    Square to;

    if ((to = make_square(rank+1, file-1)) != NO_SQUARE && !occupied(friendly, to)) ml.add(Move(from, to));
    if ((to = make_square(rank+1, file)) != NO_SQUARE && !occupied(friendly,to)) ml.add(Move(from, to));
    if ((to = make_square(rank+1, file+1)) != NO_SQUARE && !occupied(friendly,to)) ml.add(Move(from, to));
    if ((to = make_square(rank, file-1)) != NO_SQUARE && !occupied(friendly,to)) ml.add(Move(from, to));
    if ((to = make_square(rank, file+1)) != NO_SQUARE && !occupied(friendly,to)) ml.add(Move(from, to));
    if ((to = make_square(rank-1, file-1)) != NO_SQUARE && !occupied(friendly,to)) ml.add(Move(from, to));
    if ((to = make_square(rank-1, file)) != NO_SQUARE && !occupied(friendly,to)) ml.add(Move(from, to));
    if ((to = make_square(rank-1, file+1)) != NO_SQUARE && !occupied(friendly,to)) ml.add(Move(from, to));

    return ml;
}

inline MoveList movegen::pawnMoves(Square from, uint64_t friendly, uint64_t enemy, Color side) {
    MoveList ml;
    uint8_t rank = rank_of(from), file = file_of(from);
    int dir = (side == WHITE) ? 1 : -1;
    uint8_t startRank = (side == WHITE) ? 1 : 6;
    uint8_t promoRank = (side == WHITE) ? 6 : 1;
    uint64_t occupied = friendly | enemy;

    auto isOccupied = [&](Square sq) -> bool {
        return occupied & (1ULL << sq);
    };
    auto isEnemy = [&](Square sq) -> bool {
        return enemy & (1ULL << sq);
    };

    // Single push
    Square oneUp = make_square(rank + dir, file);
    if (oneUp != NO_SQUARE && !isOccupied(oneUp)) {
        if (rank == promoRank) {
            ml.add(Move(from, oneUp, PROMOTION, 0)); // knight
            ml.add(Move(from, oneUp, PROMOTION, 1)); // bishop
            ml.add(Move(from, oneUp, PROMOTION, 2)); // rook
            ml.add(Move(from, oneUp, PROMOTION, 3)); // queen
        } else {
            ml.add(Move(from, oneUp));
            // Double push
            if (rank == startRank) {
                Square twoUp = make_square(rank + 2 * dir, file);
                if (twoUp != NO_SQUARE && !isOccupied(twoUp)) {
                    ml.add(Move(from, twoUp));
                }
            }
        }
    }

    // Captures
    Square capLeft = make_square(rank + dir, file - 1);
    Square capRight = make_square(rank + dir, file + 1);

    for (Square cap : {capLeft, capRight}) {
        if (cap == NO_SQUARE) continue;
        if (isEnemy(cap)) {
            if (rank == promoRank) {
                ml.add(Move(from, cap, PROMOTION, 0));
                ml.add(Move(from, cap, PROMOTION, 1));
                ml.add(Move(from, cap, PROMOTION, 2));
                ml.add(Move(from, cap, PROMOTION, 3));
            } else {
                ml.add(Move(from, cap));
            }
        }
    }

    return ml;
}

inline MoveList movegen::chessmanMoves(Chessman cm, Square from, uint64_t friendly, uint64_t enemy, Color side) {
    switch (cm) {
        case PAWN:
            return pawnMoves(from, friendly, enemy, side);
        case KNIGHT:
            return knightMoves(from, friendly, enemy);
        case BISHOP:
            return bishopMoves(from, friendly, enemy);
        case ROOK:
            return rookMoves(from, friendly, enemy);
        case QUEEN:
            return queenMoves(from, friendly, enemy);
        case KING:
            return kingMoves(from, friendly, enemy);
        default: ;
    }
    return {};
}

inline bool movegen::isKingInCheck(Board *b, Color c) {
    Square kingSq = Square(__builtin_ctzll(b->kings(c)));
    Color enemy = ~c;
    uint64_t occ = b->allOccupied();

    return isSquareAttackedByPawn(kingSq, b->pawns(enemy), enemy)
        || isSquareAttackedByKnight(kingSq, b->knights(enemy))
        || isSquareAttackedByBishop(kingSq, b->bishops(enemy), occ)
        || isSquareAttackedByRook(kingSq, b->rooks(enemy), occ)
        || isSquareAttackedByQueen(kingSq, b->queens(enemy), occ)
        || isSquareAttackedByKing(kingSq, b->kings(enemy));
}


#endif //MOVEGEN_H
