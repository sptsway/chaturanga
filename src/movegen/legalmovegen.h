//
// Created by Swaraj Pradhan on 03/04/26.
//

#include "movegen/movegen.h"

class LegalMoveGenerator : public movegen {
public:
    MoveList allMoves(Board* b) override {
        MoveList ml;
        Color tomove = b->sideToMove();
        // cout<<(int)tomove<<"@ ";
        Color opp = Color(~tomove);

        for (Chessman cm: allChessMen) {
            uint64_t bpiece = b->pieces(cm, tomove);
           while (bpiece) {
               Square from = Square(__builtin_ctzll(bpiece)); // index of lowest set bit
               MoveList tmpml = this->chessmanMoves(
                   cm,from,
                   b->occupied(tomove), b->occupied(opp),
                   tomove
               );
               for (int j=0; j <tmpml.count; j++) {
                   // TODO optimise
                   // current it iterate over pieces' moves again
                   // a better optimisation is to store the state of the isKingInCheck somewhere in board
                   if (isLegal(b,tmpml[j])) ml.add(tmpml[j]);
               }
               // bpiece-1 -> flips all trailing 0s to 1, and rightmost 1 to 0.
               bpiece &= bpiece - 1; // clear lowest set bit
           }
        }
        return ml;
    }

    MoveList capturesOnly(Board* b) override {
        MoveList mvall = this->allMoves(b), mvcap;

        for (int i=0; i<mvall.count; i++) {
            Move mv = mvall[i];
            if (b->hasOpponentPiece(mv.to())) mvcap.add(mv);
        }

        return mvcap;
    }

    bool isLegal(Board* b, Move m) override {
        Board copy = *b;
        copy.makeMove(m);
        return !isKingInCheck(&copy, b->sideToMove());
    }
};
