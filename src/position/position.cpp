//
// Created by Swaraj Pradhan on 03/04/26.
//

#include "position.h"
#include "piece.h"


uint64_t Board::pieces(Chessman cm, Color c) const {
    switch (cm) {
        case PAWN:
            return this->pawns(c);
        case KNIGHT:
            return this->knights(c);
        case BISHOP:
            return this->bishops(c);
        case ROOK:
            return this->rooks(c);
        case QUEEN:
            return this->queens(c);
        case KING:
            return this->kings(c);
        default:;
    }
    return 0;
}

/*
 * doesnt consider special moves, only quiet is considered for time being
 */
void Board::makeMove(Move m) {
    Piece p = findPiece(m.from());
    movePiece(
        getChessManFromPiece(p),
        getColorFromPiece(p),
        m.from(), m.to()
    );
}

void Board::undoMove(Move m) {
    Piece p = findPiece(m.to());
    movePiece(
        getChessManFromPiece(p),
        getColorFromPiece(p),
        m.to(), m.from()
    );
}

void Board::setFromFEN(const std::string& fen) {
    // TODO implement me
}

void Board::putPiece(Chessman cm, Color c, Square sq) {
    if (sq == NO_SQUARE) return;
    uint64_t pos = 1ULL<<sq;
    switch (cm) {
        case PAWN:
            this->pawns_[c] |= pos;
            return;
        case KNIGHT:
            this->knights_[c] |= pos;
            return;
        case BISHOP:
            this->bishops_[c] |= pos;
            return;
        case ROOK:
            this->rooks_[c] |= pos;
            return;
        case QUEEN:
            this->queens_[c] |= pos;
            return;
        case KING:
            this->kings_[c] |= pos;
            return;
        default:;
    }
}

void Board::removePiece(Chessman cm, Color c, Square sq) {
    if (sq == NO_SQUARE) return;
    uint64_t pos = UINT64_MAX ^ 1ULL<<sq;
    switch (cm) {
        case PAWN:
            this->pawns_[c] &= pos;
            return;
        case KNIGHT:
            this->knights_[c] &= pos;
            return;
        case BISHOP:
            this->bishops_[c] &= pos;
            return;
        case ROOK:
            this->rooks_[c] &= pos;
            return;
        case QUEEN:
            this->queens_[c] &= pos;
            return;
        case KING:
            this->kings_[c] &= pos;
            return;
        default:;
    }
}

void Board::movePiece(Chessman cm, Color c, Square from, Square to) {
    removePiece(cm, c, from);
    putPiece(cm, c,to);
}

Piece Board::findPiece(Square sq) {
    if (sq == NO_SQUARE) return NO_PIECE;
    for (Piece p: allPieces) {
        if (isPieceLocated(
            getChessManFromPiece(p),
            getColorFromPiece(p),
            sq)
        ) return p;
    }
    return NO_PIECE;
}

bool Board::isPieceLocated(Chessman cm, Color c, Square sq) {
    uint64_t bitsq = 1ULL<<sq;
    switch (cm) {
        case PAWN:
            return this->pawns_[c] & bitsq;
        case KNIGHT:
            return this->knights_[c] & bitsq;
        case BISHOP:
            return this->bishops_[c] & bitsq;
        case ROOK:
            return this->rooks_[c] & bitsq;
        case QUEEN:
            return this->queens_[c] & bitsq;
        case KING:
            return this->kings_[c] & bitsq;
        default:;
    }
    return false;
}