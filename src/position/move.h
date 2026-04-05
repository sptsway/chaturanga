//
// Created by Swaraj Pradhan on 03/04/26.
//

#ifndef MOVE_H
#define MOVE_H
#include "chessman.h"
#include "square.h"

// Bits layout:
// 0-5:   from square (0-63)
// 6-11:  to square (0-63)
// 12-13: promotion piece (knight=0, bishop=1, rook=2, queen=3)
// 14-15: flags (quiet=0, promotion=1, en passant=2, castling=3)

enum MoveFlag : uint8_t {
    QUIET      = 0,
    PROMOTION  = 1,
    EN_PASSANT = 2,
    CASTLING   = 3
};

class Move {
public:
    Move() : data_(0) {}
    Move(Square from, Square to, MoveFlag flag = QUIET, uint8_t promo = 0)
        : data_(from | (to << 6) | (promo << 12) | (flag << 14)) {}

    Square from() const { return Square(data_ & 0x3F); }
    Square to() const { return Square((data_ >> 6) & 0x3F); }
    MoveFlag flag() const { return MoveFlag((data_ >> 14) & 0x3); }
    Chessman promotion() const {
        return Chessman(((data_ >> 12) & 0x3) + KNIGHT);
    }

    std::string Move::toString() const {
        std::string s = ::to_string(from()) + ::to_string(to());
        if (flag() == PROMOTION) {
            const char promoChars[] = "nbrq";
            s += promoChars[promotion() - KNIGHT];
        }

        return s;
    }

    bool operator==(Move other) const { return data_ == other.data_; }
    bool isNull() const { return data_ == 0; }

private:
    uint16_t data_;
};

#endif //MOVE_H
