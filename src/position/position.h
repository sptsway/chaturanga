//
// Created by Swaraj Pradhan on 03/04/26.
//

#ifndef POSITION_H
#define POSITION_H

#include <cstdint>
#include <string>

#include "color.h"
#include "move.h"
#include "pieces.h"
#include "square.h"

using namespace std;

class Board {
private:
    uint64_t pawns_[2];
    uint64_t knights_[2];
    uint64_t bishops_[2];
    uint64_t rooks_[2];
    uint64_t queens_[2];
    uint64_t kings_[2];

    uint64_t occupied_[2];
    uint64_t allOccupied_;

    Color sideToMove_;
    uint8_t castlingRights_;
    Square enPassantSquare_;
    uint8_t halfmoveClock_;
    uint16_t fullmoveNumber_;
    uint64_t zobristHash_;

public:
    // Accessors
    uint64_t pawns(Color c) const;
    uint64_t knights(Color c) const;
    uint64_t bishops(Color c) const;
    uint64_t rooks(Color c) const;
    uint64_t queens(Color c) const;
    uint64_t kings(Color c) const;
    uint64_t occupied(Color c) const;
    uint64_t allOccupied() const;

    Color sideToMove() const;
    uint8_t castlingRights() const;
    Square enPassantSquare() const;
    uint8_t halfmoveClock() const;
    uint16_t fullmoveNumber() const;
    uint64_t zobristHash() const;

    // Mutators
    void makeMove(Move m);
    void undoMove(Move m);
    void setFromFEN(const std::string& fen);
    void putPiece(Chessman cm, Color c, Square sq);
    void removePiece(Chessman cm, Color c, Square sq);
    void movePiece(Chessman cm, Color c, Square from, Square to);
};

#endif //POSITION_H
