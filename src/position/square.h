//
// Created by Swaraj Pradhan on 03/04/26.
//

#ifndef SQUARE_H
#define SQUARE_H
#include <cstdint>

enum Square : uint8_t {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    NO_SQUARE = 64
};

// rank,file :: rowno,columnno
inline Square make_square(int rank, int file) {
    if (file < 0 || file >= 8 || rank < 0 || rank >= 8)
        return NO_SQUARE;
    return static_cast<Square>(rank * 8 + file);
}

// rank from square
inline uint8_t rank_of(Square sq) {
    return sq/8;
}

// file from square
inline uint8_t file_of(Square sq) {
    return sq%8;
}

// file from square
inline std::string to_string(Square sq) {
    char file = 'a' + file_of(sq);
    char rank = '1' + rank_of(sq);
    return {file, rank};
}


#endif //SQUARE_H
