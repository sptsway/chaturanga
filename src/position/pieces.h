//
// Created by Swaraj Pradhan on 03/04/26.
//

#ifndef PIECES_H
#define PIECES_H
#include <cstdint>

enum Chessman : uint8_t {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    NO_CHESSMAN
};

const Chessman allPieces[] = {
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING,
};

#endif //PIECES_H
