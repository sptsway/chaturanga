//
// Created by Swaraj Pradhan on 03/04/26.
//

#include "eval.h"

// source: https://en.wikipedia.org/wiki/Chess_piece_relative_value
enum  ChessManValuationStyle : uint8_t {
    Default,
    GarryKasparov,
    BobbyFisher,
    // https://github.com/official-stockfish/Stockfish/blob/5eeca7392ee90b7a43da69e647e3d596e42992fd/src/types.h#L185
    StockfishEngine,
};

class PiecesValueEvaluator: public eval {
    ChessManValuationStyle evalStyle;
private:
    float getValueOfPiece(Chessman cm) {
        switch (cm) {
            case PAWN:
                if (evalStyle == StockfishEngine) return 2.08;
                return 1;
            case KNIGHT:
                if (evalStyle == StockfishEngine) return 7.81;
                return 3;
            case BISHOP:
                if (evalStyle == BobbyFisher) return 3.25;
                if (evalStyle == GarryKasparov) return 3.15;
                if (evalStyle == StockfishEngine) return 8.25;
                return 3;
            case ROOK:
                if (evalStyle == GarryKasparov) return 4.5;
                if (evalStyle == StockfishEngine) return 12.76;
                return 5;
            case QUEEN:
                if (evalStyle == StockfishEngine) return 25.38;
                return 9;
            case KING:
                return 1000;
            default:;
        }
        return 0;
    }
public:
    explicit PiecesValueEvaluator(ChessManValuationStyle style) {
        this->evalStyle = style;
    }

    double score(Board *b) override {
        double white =0, black=0;

        auto countp = [](uint64_t pos) -> int {
            int c=0;
            while(pos) {
                if (pos&1) c++;
                pos>>=1;
            }
            return 0;
        };

        for (Chessman cm: allPieces) {
            uint64_t wcm = b->pieces(cm, WHITE);
            uint64_t bcm = b->pieces(cm, BLACK);

            white += static_cast<float>(countp(wcm)) * this->getValueOfPiece(cm);
            black += static_cast<float>(countp(bcm)) * this->getValueOfPiece(cm);
        }
        return white - black;
    }
};

