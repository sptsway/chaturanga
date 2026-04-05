//
// Created by Swaraj Pradhan on 04/04/26.
//

#ifndef PIECE_H
#define PIECE_H
#include "color.h"


enum Piece : uint8_t {
    WHITE_PAWN, BLACK_PAWN,
    WHITE_KNIGHT, BLACK_KNIGHT,
    WHITE_BISHOP, BLACK_BISHOP,
    WHITE_ROOK, BLACK_ROOK,
    WHITE_QUEEN, BLACK_QUEEN,
    WHITE_KING, BLACK_KING,
    NO_PIECE
};

inline extern Color getColor(Piece p) {
    if (p%2) return BLACK;
    return WHITE;
}


inline extern Chessman getChessman(Piece p) {
    return Chessman(p/2);
}

const Piece allPieces[] = {
    WHITE_PAWN, BLACK_PAWN,
    WHITE_KNIGHT, BLACK_KNIGHT,
    WHITE_BISHOP, BLACK_BISHOP,
    WHITE_ROOK, BLACK_ROOK,
    WHITE_QUEEN, BLACK_QUEEN,
    WHITE_KING, BLACK_KING,
};


#endif //PIECE_H
