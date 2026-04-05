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

inline extern Color getColorFromPiece(Piece p) {
    switch (p) {
        case WHITE_PAWN:
        case WHITE_KNIGHT:
        case WHITE_BISHOP:
        case WHITE_ROOK:
        case WHITE_QUEEN:
        case WHITE_KING:
            return WHITE;
       case BLACK_PAWN:
       case BLACK_KNIGHT:
       case BLACK_BISHOP:
       case BLACK_ROOK:
       case BLACK_QUEEN:
       case BLACK_KING:
            return BLACK;
        default:;
    }
    return WHITE;
}


inline extern Chessman getChessManFromPiece(Piece p) {
    switch (p) {
        case WHITE_PAWN:
        case BLACK_PAWN:
            return PAWN;

        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            return KNIGHT;

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            return BISHOP;

        case WHITE_ROOK:
        case BLACK_ROOK:
            return ROOK;

        case WHITE_QUEEN:
        case BLACK_QUEEN:
            return QUEEN;

        case WHITE_KING:
        case BLACK_KING:
            return KING;
        default:;
    }
    return NO_CHESSMAN;
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
