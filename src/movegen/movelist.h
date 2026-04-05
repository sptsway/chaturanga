//
// Created by Swaraj Pradhan on 04/04/26.
//

#ifndef MOVELIST_H
#define MOVELIST_H
#include "position/move.h"

struct MoveList {
    Move moves[256];
    int count = 0;

    void add(Move m) { moves[count++] = m; }
    Move operator[](int i) const { return moves[i]; }
};

#endif //MOVELIST_H
