//
// Created by Swaraj Pradhan on 03/04/26.
//

#include "search.h"

#include "movegen.h"
#include "movelist.h"

class MinMaxDFS : search {
    SearchResult getBestMove(Board *b, movegen *mg, eval *ev, int depth) override {
        if (depth == 0) return SearchResult{
            .bestMove = Move(),
            .score = ev->score(b),
            .depth = 0
        };

        SearchResult bestRes = SearchResult{
            .score = b->sideToMove() == WHITE? WORST_WHITE_SCORE: WORST_BLACK_SCORE,
        };

        auto isBetterResult = [&](SearchResult res) {
            if (b->sideToMove() == WHITE) {
                return res.score > bestRes.score;
            }
            return res.score < bestRes.score;
        };


        MoveList mv = mg->allMoves(b);
        for (int i=0;i<mv.count;i++) {
            Board copy = *b;
            copy.makeMove(mv[i]);

            SearchResult res = this->getBestMove(&copy, mg, ev, depth-1);
            if (isBetterResult(res)) {
                bestRes = SearchResult{
                    .bestMove = mv[i],
                    .score = res.score,
                    .depth = depth
                };
            }
        }
        return bestRes;
    }
};
