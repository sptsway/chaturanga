//
// Created by Swaraj Pradhan on 03/04/26.
//

#ifndef EVAL_H
#define EVAL_H
#include "position.h"

constexpr double BEST_WHITE_SCORE = 64 * 1000;
constexpr double BEST_BLACK_SCORE = - 64 * 1000;
constexpr double WORST_WHITE_SCORE = - 64 * 1000;
constexpr double WORST_BLACK_SCORE = 64 * 1000;

class eval {
public:
    // Tells score from the board
    // +ve -> white is winning
    // -ve -> black is winning
    virtual double score(Board *b) = 0;
    virtual ~eval();
};



#endif //EVAL_H
