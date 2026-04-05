//
// Created by Swaraj Pradhan on 05/04/26.
//

#include "game/game.h"

#include "eval/eval.h"
#include "movegen/movegen.h"
#include "position/position.h"
#include "search/search.h"

class Chess : public game {
private:
    Board* b_{};
    ::search* s_{};
    movegen* mg_{};
    eval* ev_{};
    Color engineColor_;
    int depth_{};
    bool print_;

public:
    Chess(Board* b, ::search* s, movegen* mg, eval* ev, Color userColor, int depth, bool print);

    void start(std::istream& in = std::cin, std::ostream& out = std::cout) override;
    void makeMove(Move m, std::ostream& out) override;
    Move receiveMove(std::istream& in) override ;
};

inline Chess::Chess(Board *b,
                    ::search *s,
                    movegen *mg,
                    eval *ev,
                    Color engineColor,
                    int depth,
                    bool print
                    ) : game(), b_(b), s_(s), mg_(mg), ev_(ev), engineColor_(engineColor), depth_(depth), print_(print) {
}

inline void Chess::start(std::istream& in, std::ostream& out) {
    // game begins ...
    while (true) {
        if (b_->sideToMove() == engineColor_) {
            SearchResult res = s_->getBestMove(b_,mg_,ev_, depth_);
            if (engineColor_ == WHITE? (res.score < -500) : (res.score > 500) ) {
                out<<"--- resign ---\n"; break;
            }
            makeMove(res.bestMove, out);
            b_->makeMove(res.bestMove);
            if (this->print_) b_->print(out);
        } else {
            Move mv = receiveMove(in);
            b_->makeMove(mv);
        }
    }
}

inline void Chess::makeMove(Move m, std::ostream& out) {
    out<<m.toString()<<endl;
}

inline Move Chess::receiveMove(std::istream& in) {
    // TODO -> validate user's move
    string move;
    in>>move;
    return parseUserMove(move);
}
