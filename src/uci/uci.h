//
// Created by Swaraj Pradhan on 03/04/26.
//

#ifndef UCI_H
#define UCI_H

#include <sstream>

#include "game/game.h"

#include "eval/eval.h"
#include "movegen/movegen.h"
#include "position/position.h"
#include "search/search.h"


class UCI : public game {
private:
    Board* b_{};
    ::search* s_{};
    movegen* mg_{};
    eval* ev_{};
    int depth_{};

public:
    UCI(Board *b,::search* s, movegen* mg, eval* ev, int depth);

    void start(std::istream& in = std::cin, std::ostream& out = std::cout) override;
    void makeMove(Move m, std::ostream& out) override;
    Move receiveMove(std::istream& in) override ;
    void uciInfo(std::ostream& out);
};

inline UCI::UCI(
    Board *b,
    ::search *s,
    movegen *mg,
    eval *ev,
    int defaultDepth
    ) : game(), b_(b), s_(s), mg_(mg), ev_(ev), depth_(defaultDepth) {
}

inline void UCI::start(std::istream& in, std::ostream& out) {
    std::string line;

    // game begins ...
    while (std::getline(in, line)) {
        // info of uci
        if (line == "uci") {
            this->uciInfo(out);
            out << "uciok" << std::endl;
        } // ready init
        else if (line == "isready") {
            out << "readyok" << std::endl;
        } // start new board
        else if (line == "ucinewgame") {
            *b_ = Board(); // reset board
        } // board setup
        else if (line.rfind("position", 0) == 0) {
            // parse "position startpos" or "position fen <fen>"
            // then apply moves after "moves" keyword
            std::istringstream ss(line);
            std::string token;
            ss >> token; // "position"
            ss >> token;

            if (token == "startpos") {
                b_->setFromFEN(INIT_BOARD_FEN);
            } else if (token == "fen") {
                std::string fen;
                while (ss >> token && token != "moves") {
                    if (!fen.empty()) fen += " ";
                    fen += token;
                }
                b_->setFromFEN(fen);
                if (token == "moves") this->receiveMove(ss);
                continue;
            }
            // skip past "moves" keyword
            if (ss >> token && token == "moves") this->receiveMove(ss);
        } // tell the best move
        else if (line.rfind("go", 0) == 0) {
            int depth = depth_;
            std::istringstream ss(line);
            std::string token;
            ss >> token; // "go"
            while (ss >> token) {
                if (token == "depth" && ss >> token) {
                    depth = std::stoi(token);
                }
            }
            SearchResult res = s_->getBestMove(b_, mg_, ev_, depth);
            this->makeMove(res.bestMove, out);
        } else if (line == "quit") {
            break;
        }
    }
}

inline void UCI::makeMove(Move m, std::ostream& out) {
    out << "bestmove " << m.toString() << std::endl;
}

inline Move UCI::receiveMove(std::istream& in) {
    string token;
    while (in >> token) {
        Move m = game::parseUserMove(token);
        this->b_->makeMove(m);
    }
    // just set the board, return garbage move
    return Move();
}

inline void UCI::uciInfo(std::ostream& out) {
    out << "id name Chaturanga" << std::endl;
    out << "id author Swaraj" << std::endl;
}



#endif //UCI_H
