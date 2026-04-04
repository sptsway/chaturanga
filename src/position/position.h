//
// Created by Swaraj Pradhan on 03/04/26.
//

#ifndef POSITION_H
#define POSITION_H

#include <string>

#include "color.h"
#include "move.h"
#include "chessman.h"
#include "piece.h"
#include "square.h"

using namespace std;

class Board {
private:
    uint64_t pawns_[2]{};
    uint64_t knights_[2]{};
    uint64_t bishops_[2]{};
    uint64_t rooks_[2]{};
    uint64_t queens_[2]{};
    uint64_t kings_[2]{};

    uint64_t occupied_[2]{};
    uint64_t allOccupied_{};

    Color sideToMove_;
    uint8_t castlingRights_{};
    Square enPassantSquare_;
    uint8_t halfmoveClock_{};
    uint16_t fullmoveNumber_{};
    uint64_t zobristHash_{};

public:
    // --- constructors ---
    Board() = default;

    // --- accessors ---
    uint64_t pawns(Color c) const { return pawns_[c];}
    uint64_t knights(Color c) const { return knights_[c];}
    uint64_t bishops(Color c) const { return bishops_[c];}
    uint64_t rooks(Color c) const { return rooks_[c];}
    uint64_t queens(Color c) const { return queens_[c];}
    uint64_t kings(Color c) const { return kings_[c];}
    uint64_t occupied(Color c) const { return occupied_[c];}
    uint64_t allOccupied() const { return allOccupied_;}

    Color sideToMove() const { return sideToMove_;}
    uint8_t castlingRights() const { return castlingRights_;}
    Square enPassantSquare() const { return enPassantSquare_;}
    uint8_t halfmoveClock() const { return halfmoveClock_;}
    uint16_t fullmoveNumber() const { return fullmoveNumber_;}
    uint64_t zobristHash() const { return zobristHash_;}

    // --- mutators ---
    void makeMove(Move m);
    void undoMove(Move m);
    void setFromFEN(const std::string& fen);
    void putPiece(Chessman cm, Color c, Square sq);
    void removePiece(Chessman cm, Color c, Square sq);
    void movePiece(Chessman cm, Color c, Square from, Square to);

    // --- helpers ---
    // gets pos given a piece and color
    uint64_t pieces(Chessman cm, Color c) const;
    // is piece located
    bool isPieceLocated(Chessman cm, Color c, Square sq);
    // gets piece at position
    Piece findPiece(Square sq);
    // if the square has black piece
    bool hasBlackPiece(Square sq);
    // if the square has white piece
    bool hasWhitePiece(Square sq);
};

#endif //POSITION_H
