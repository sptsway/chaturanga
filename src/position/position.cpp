//
// Created by Swaraj Pradhan on 03/04/26.
//

#include "position.h"


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