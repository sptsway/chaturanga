//
// Created by Swaraj Pradhan on 03/04/26.
//

#ifndef SEARCH_H
#define SEARCH_H
#include "movegen/movegen.h"
#include "eval/eval.h"
#include "position/move.h"

struct SearchResult {
    Move bestMove;
    double score;
    int depth;
};

class search {
public:
    virtual ~search() = default;

    virtual SearchResult getBestMove(Board* b, movegen* mg, eval* ev, int depth) =0;
};



#endif //SEARCH_H
