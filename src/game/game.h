//
// Created by Swaraj Pradhan on 05/04/26.
//

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>

#include "move.h"

class game {
public:
    virtual ~game() = default;

    game();
    virtual void start(std::istream& in, std::ostream& out) =0;
    virtual void makeMove(Move m, std::ostream& out);
    virtual Move receiveMove(std::istream& in);
    static Move parseUserMove(const std::string& input);
};

inline Move game::parseUserMove(const std::string& input) {
    if (input.length() < 4) return Move(); // invalid

    int fromFile = input[0] - 'a';
    int fromRank = input[1] - '1';
    int toFile = input[2] - 'a';
    int toRank = input[3] - '1';

    Square from = make_square(fromRank, fromFile);
    Square to = make_square(toRank, toFile);

    if (from == NO_SQUARE || to == NO_SQUARE) return Move();

    // Promotion
    if (input.length() == 5) {
        uint8_t promo;
        switch (input[4]) {
            case 'n': promo = 0; break;
            case 'b': promo = 1; break;
            case 'r': promo = 2; break;
            case 'q': promo = 3; break;
            default: return Move();
        }
        return {from, to, PROMOTION, promo};
    }

    return {from, to};
}
#endif //GAME_H
