#include "eval/piecesvalueeval.h"
#include "movegen/movegen.h"
#include "movegen/legalmovegen.h"
#include "search/minmaxdfs.h"
#include "position/position.h"
#include "game/chess.h"

#include <string>
#include <cstring>
#include <sstream>
#include "uci/uci.h"

using namespace std;

void printHelp(const char* program) {
    std::cout << "Usage: " << program << " [options]\n"
              << "\nOptions:\n"
              << "  --fen <string>      Starting position (default: standard)\n"
              << "  --color <w|b>       Engine plays as white or black (default: b)\n"
              << "  --depth <int>       Search depth (default: 4)\n"
              << "  --movegen <type>    Move generator: all_legal (default: legal)\n"
              << "  --eval <type>       Evaluation style: simple, kasparov, fisher, stockfish (default: stockfish)\n"
              << "  --game <type>       cli game / uci game, default - cli \n"
              << "  --noprint           dont print board after engine's move, default - not present \n"
              << "  --help              Show this help message\n";
}

signed main(int argc, const char* argv[]) {
    std::string fen = INIT_BOARD_FEN;
    Color engineColor = BLACK;
    int depth = 4;
    std::string movegenType = "all_legal";
    std::string evalType = "stockfish";
    string gametype = "cli";
    bool print = true;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            printHelp(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--fen") == 0 && i + 1 < argc) {
            fen = argv[++i];
        } else if (strcmp(argv[i], "--color") == 0 && i + 1 < argc) {
            i++;
            engineColor = (strcmp(argv[i], "w") == 0) ? WHITE : BLACK;
        } else if (strcmp(argv[i], "--depth") == 0 && i + 1 < argc) {
            depth = std::stoi(argv[++i]);
        } else if (strcmp(argv[i], "--movegen") == 0 && i + 1 < argc) {
            movegenType = argv[++i];
        } else if (strcmp(argv[i], "--eval") == 0 && i + 1 < argc) {
            evalType = argv[++i];
        }  else if (strcmp(argv[i], "--game") == 0 && i + 1 < argc) {
            gametype = argv[++i];
        } else if (strcmp(argv[i], "--noprint") == 0) {
           print = false;
        }
    }

    // Eval
    ChessManValuationStyle evalStyle = StockfishEngine;
    if (evalType == "simple") evalStyle = Simple;
    else if (evalType == "kasparov") evalStyle = GarryKasparov;
    else if (evalType == "fisher") evalStyle = BobbyFisher;

    LegalMoveGenerator mg;
    PiecesValueEvaluator ev(evalStyle);
    MinMaxDFS s;
    game *game;
    if (gametype == "uci") {
        Board b;
        game = new UCI(&b, &s, &mg, &ev, depth);
    } else {
        Board b; b.setFromFEN(fen);
        game = new Chess(&b, &s, &mg, &ev, engineColor, depth, print);
    }
    game->start(cin, cout);


    return 0;
}