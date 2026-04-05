//
// Created by Swaraj Pradhan on 05/04/26.
//

#include "game.h"

#include "eval.h"
#include "movegen.h"
#include "position.h"
#include "search.h"

class Game : game {
private:
    Board* b_{};
    search::search* s_{};
    movegen* mg_{};
    eval* ev_{};
    Color engineColor_;
    int depth_{};

public:
    Game(Board* b, search::search* s, movegen* mg, eval* ev, Color userColor, int depth);
    void start(std::istream& in = std::cin, std::ostream& out = std::cout) override;
    void makeMove(Move m, std::ostream& out) override;
    Move receiveMove(std::istream& in) override ;
};

Game::Game(Board *b,
    search::search *s,
    movegen *mg,
    eval *ev,
    Color engineColor,
    int depth
) : b_(b), s_(s), mg_(mg), ev_(ev), engineColor_(engineColor), depth_(depth), game() {

}

void Game::start(std::istream& in, std::ostream& out) {
    // game begins ...
    while (true) {
        if (b_->sideToMove() == engineColor_) {
            SearchResult res = s_->getBestMove(b_,mg_,ev_, depth_);
            if (engineColor_ == WHITE? (res.score < -500) : (res.score > 500) ) {
                out<<"--- resign ---\n"; break;
            }
            makeMove(res.bestMove, out);
            b_->makeMove(res.bestMove);
        } else {
            Move mv = receiveMove(in);
            b_->makeMove(mv);
        }
    }
}

void Game::makeMove(Move m, std::ostream& out) {
    out<<m.toString()<<endl;
}

Move Game::receiveMove(std::istream& in) {
    // TODO -> validate user's move
    string move;
    in>>move;
    return parseUserMove(move);
}
