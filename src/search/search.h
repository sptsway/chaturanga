//
// Created by Swaraj Pradhan on 03/04/26.
//

#ifndef SEARCH_H
#define SEARCH_H
#include "eval.h"
#include "move.h"

class movegen;
class Board;

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
