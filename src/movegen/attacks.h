//
// Created by Swaraj Pradhan on 05/04/26.
//

#ifndef ATTACKS_H
#define ATTACKS_H
#include <cstdint>

#include "color.h"
#include "square.h"

inline bool isSquareAttackedByKnight(Square sq, uint64_t enemyKnights) {
    uint8_t rank = rank_of(sq), file = file_of(sq);
    Square targets[] = {
        make_square(rank+2, file-1), make_square(rank+2, file+1),
        make_square(rank+1, file+2), make_square(rank+1, file-2),
        make_square(rank-1, file+2), make_square(rank-1, file-2),
        make_square(rank-2, file+1), make_square(rank-2, file-1)
    };
    for (Square s : targets) {
        if (s != NO_SQUARE && (enemyKnights & (1ULL << s))) return true;
    }
    return false;
}

inline bool isSquareAttackedByBishop(Square sq, uint64_t enemyBishops, uint64_t occupied) {
    uint8_t rank = rank_of(sq), file = file_of(sq);
    int dirs[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
    for (auto& d : dirs) {
        for (int i = 1; i < 8; i++) {
            Square s = make_square(rank + d[0]*i, file + d[1]*i);
            if (s == NO_SQUARE) break;
            if (enemyBishops & (1ULL << s)) return true;
            if (occupied & (1ULL << s)) break;
        }
    }
    return false;
}

inline bool isSquareAttackedByRook(Square sq, uint64_t enemyRooks, uint64_t occupied) {
    uint8_t rank = rank_of(sq), file = file_of(sq);
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    for (auto& d : dirs) {
        for (int i = 1; i < 8; i++) {
            Square s = make_square(rank + d[0]*i, file + d[1]*i);
            if (s == NO_SQUARE) break;
            if (enemyRooks & (1ULL << s)) return true;
            if (occupied & (1ULL << s)) break;
        }
    }
    return false;
}

inline bool isSquareAttackedByQueen(Square sq, uint64_t enemyQueens, uint64_t occupied) {
    return isSquareAttackedByBishop(sq, enemyQueens, occupied)
        || isSquareAttackedByRook(sq, enemyQueens, occupied);
}

inline bool isSquareAttackedByPawn(Square sq, uint64_t enemyPawns, Color enemyColor) {
    uint8_t rank = rank_of(sq), file = file_of(sq);
    int dir = (enemyColor == WHITE) ? -1 : 1; // pawns attack from below if white
    Square left = make_square(rank + dir, file - 1);
    Square right = make_square(rank + dir, file + 1);
    if (left != NO_SQUARE && (enemyPawns & (1ULL << left))) return true;
    if (right != NO_SQUARE && (enemyPawns & (1ULL << right))) return true;
    return false;
}

inline bool isSquareAttackedByKing(Square sq, uint64_t enemyKing) {
    uint8_t rank = rank_of(sq), file = file_of(sq);
    for (int dr = -1; dr <= 1; dr++) {
        for (int df = -1; df <= 1; df++) {
            if (dr == 0 && df == 0) continue;
            Square s = make_square(rank + dr, file + df);
            if (s != NO_SQUARE && (enemyKing & (1ULL << s))) return true;
        }
    }
    return false;
}

#endif //ATTACKS_H
