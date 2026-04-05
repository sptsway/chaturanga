//
// Created by Swaraj Pradhan on 03/04/26.
//

#include "position.h"
#include "piece.h"
#include <sstream>

uint64_t Board::pieces(Chessman cm, Color c) const {
    switch (cm) {
        case PAWN:
            return this->pawns(c);
        case KNIGHT:
            return this->knights(c);
        case BISHOP:
            return this->bishops(c);
        case ROOK:
            return this->rooks(c);
        case QUEEN:
            return this->queens(c);
        case KING:
            return this->kings(c);
        default:;
    }
    return 0;
}

// TODO -> update the castling and enpassant variables
void Board::makeMove(Move m) {
    Piece p = findPiece(m.from());
    Piece captured = findPiece(m.to());
    if (captured != NO_PIECE) {
        removePiece(getChessman(captured), getColor(captured), m.to());
    }

    if (m.flag() == PROMOTION) {
        removePiece(getChessman(p), getColor(p), m.from());
        // remove captured piece if any
        putPiece(m.promotion(), getColor(p), m.to());
    }else if (m.flag() == EN_PASSANT) {
        movePiece(getChessman(p), getColor(p), m.from(), m.to());
        // captured pawn is behind the destination, hence m.from() is used
        Square capSq = make_square(file_of(m.to()), rank_of(m.from()));
        removePiece(PAWN, ~getColor(p), capSq);
    }else if (m.flag() == CASTLING) {
        movePiece(KING, getColor(p), m.from(), m.to());
        // move the rook too
        if (file_of(m.to()) == 6) { // kingside
            movePiece(ROOK, getColor(p), make_square(7, rank_of(m.from())), make_square(5, rank_of(m.from())));
        } else { // queenside
            movePiece(ROOK, getColor(p), make_square(0, rank_of(m.from())), make_square(3, rank_of(m.from())));
        }
    }else {
        // quiet
        movePiece(
            getChessman(p),
            getColor(p),
            m.from(), m.to()
        );
    }
    sideToMove_ = ~sideToMove_;
    if (sideToMove_ == WHITE) fullmoveNumber_ ++;
}

// doesnt handle special undo moves yet
void Board::undoMove(Move m) {
    Piece p = findPiece(m.to());
    movePiece(
        getChessman(p),
        getColor(p),
        m.to(), m.from()
    );
    sideToMove_ = ~sideToMove_;
    if (sideToMove_ == WHITE) fullmoveNumber_ --;
}
// example FEN: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
// number represents number of vacant squares
void Board::setFromFEN(const std::string& fen) {
    // Clear everything
    for (Color c: {BLACK, WHITE}) {
        pawns_[c] = knights_[c] = bishops_[c] = 0;
        rooks_[c] = queens_[c] = kings_[c] = 0;
        occupied_[c] = 0;
    }
    allOccupied_ = 0;

    std::istringstream ss(fen);
    std::string pieces, side, castling, ep;
    int half, full;
    ss >> pieces >> side >> castling >> ep >> half >> full;

    // 1. Piece placement
    int rank = 7, file = 0;
    for (char ch : pieces) {
        if (ch == '/') {
            rank--;
            file = 0;
        } else if (ch >= '1' && ch <= '8') {
            file += ch - '0';
        } else {
            Color c = isupper(ch) ? WHITE : BLACK;
            Chessman cm;
            switch (tolower(ch)) {
                case 'p': cm = PAWN; break;
                case 'n': cm = KNIGHT; break;
                case 'b': cm = BISHOP; break;
                case 'r': cm = ROOK; break;
                case 'q': cm = QUEEN; break;
                case 'k': cm = KING; break;
                default: file++; continue;
            }
            putPiece(cm, c, make_square(file, rank));
            file++;
        }
    }

    // 2. Side to move
    sideToMove_ = (side == "w") ? WHITE : BLACK;

    // 3. Castling rights
    castlingRights_ = 0;
    if (castling != "-") {
        for (char ch : castling) {
            if (ch == 'K') castlingRights_ |= 0x1;
            if (ch == 'Q') castlingRights_ |= 0x2;
            if (ch == 'k') castlingRights_ |= 0x4;
            if (ch == 'q') castlingRights_ |= 0x8;
        }
    }

    // 4. En passant
    if (ep == "-") {
        enPassantSquare_ = NO_SQUARE;
    } else {
        int epFile = ep[0] - 'a';
        int epRank = ep[1] - '1';
        enPassantSquare_ = make_square(epFile, epRank);
    }

    // 5 & 6
    halfmoveClock_ = half;
    fullmoveNumber_ = full;
}

void Board::putPiece(Chessman cm, Color c, Square sq) {
    if (sq == NO_SQUARE) return;
    uint64_t pos = 1ULL<<sq;
    this->occupied_[c] |= pos;
    this->allOccupied_ |= pos;
    switch (cm) {
        case PAWN:
            this->pawns_[c] |= pos;
            return;
        case KNIGHT:
            this->knights_[c] |= pos;
            return;
        case BISHOP:
            this->bishops_[c] |= pos;
            return;
        case ROOK:
            this->rooks_[c] |= pos;
            return;
        case QUEEN:
            this->queens_[c] |= pos;
            return;
        case KING:
            this->kings_[c] |= pos;
            return;
        default:;
    }
}

void Board::removePiece(Chessman cm, Color c, Square sq) {
    if (sq == NO_SQUARE) return;
    uint64_t pos = ~(1ULL<<sq);
    this->occupied_[c] &= pos;
    this->allOccupied_ &= pos;
    switch (cm) {
        case PAWN:
            this->pawns_[c] &= pos;
            return;
        case KNIGHT:
            this->knights_[c] &= pos;
            return;
        case BISHOP:
            this->bishops_[c] &= pos;
            return;
        case ROOK:
            this->rooks_[c] &= pos;
            return;
        case QUEEN:
            this->queens_[c] &= pos;
            return;
        case KING:
            this->kings_[c] &= pos;
            return;
        default:;
    }
}

void Board::movePiece(Chessman cm, Color c, Square from, Square to) {
    removePiece(cm, c, from);
    putPiece(cm, c,to);
}

Piece Board::findPiece(Square sq) {
    if (sq == NO_SQUARE) return NO_PIECE;
    for (Piece p: allPieces) {
        if (isPieceLocated(
            getChessman(p),
            getColor(p),
            sq)
        ) return p;
    }
    return NO_PIECE;
}

bool Board::isPieceLocated(Chessman cm, Color c, Square sq) {
    uint64_t bitsq = 1ULL<<sq;
    switch (cm) {
        case PAWN:
            return this->pawns_[c] & bitsq;
        case KNIGHT:
            return this->knights_[c] & bitsq;
        case BISHOP:
            return this->bishops_[c] & bitsq;
        case ROOK:
            return this->rooks_[c] & bitsq;
        case QUEEN:
            return this->queens_[c] & bitsq;
        case KING:
            return this->kings_[c] & bitsq;
        default:;
    }
    return false;
}

bool Board::hasBlackPiece(Square sq) {
    if (sq == NO_SQUARE) return false;
    uint64_t bitsq = 1ULL<<sq;
    return occupied_[BLACK] & bitsq;
}
// if the square has white piece
bool Board::hasWhitePiece(Square sq) {
    if (sq == NO_SQUARE) return false;
    uint64_t bitsq = 1ULL<<sq;
    return occupied_[WHITE] & bitsq;
}

// if the square has white piece
bool Board::hasOpponentPiece(Square sq) {
    if (sq == NO_SQUARE) return false;
    if (this->sideToMove_) return hasWhitePiece(sq);
    return hasBlackPiece(sq);
}