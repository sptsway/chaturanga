# Chaturanga

Chaturanga is a chess engine written in C++ from scratch. It currently takes a classical approach — relying on handcrafted evaluation and tree search.

Its architecture is built around pluggable networks, making it straightforward to introduce ML-based components down the line. It follows a three-network architecture:

- **Policy Network** — generates legal and candidate moves from a given position
- **Search Tree** — explores the game tree using depth-limited minimax
- **Value Network** — evaluates board positions to determine which side is winning

Each component is a pluggable interface — swap in a different evaluation strategy, move generator, or search algorithm without changing the rest of the engine. The same architecture could support a neural network evaluator or a learned move-ordering policy with minimal changes.

Named after [Chaturanga](https://en.wikipedia.org/wiki/Chaturanga), the ancient Indian game from which modern chess evolved.

## Build

```bash
make
```

## Usage

```bash
./chaturanga [options]
```

### Options

| Flag | Description | Default |
|------|-------------|---------|
| `--color <w\|b>` | Engine plays as white or black | `b` |
| `--depth <int>` | Search depth | `4` |
| `--eval <type>` | Evaluation: `simple`, `kasparov`, `fisher`, `stockfish` | `stockfish` |
| `--fen <string>` | Starting position in FEN notation | Standard starting position |
| `--help` | Show help message | |

### Example

```bash
# Play as white against the engine (black) at depth 5
./chaturanga --color b --depth 5

# Play from a custom position
./chaturanga --fen "r1bqkbnr/pppppppp/2n5/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 1 2"
```

### Move Format

Moves are entered in long algebraic notation: `<from><to>[promotion]`

- `e2e4` — pawn to e4
- `g1f3` — knight to f3
- `e7e8q` — pawn promotes to queen

## Example Game

Human plays white, engine (depth 4, Stockfish piece-valuation-eval) plays black:

### CLI:
```
  a b c d e f g h        e2e4       a b c d e f g h        d2d4       a b c d e f g h
8 r n b q k b n r 8      ───►     8 r n b q k b n r 8      ───►     8 r n b q k b n r 8
7 p p p p p p p p 7     b7b6      7 p . p p p p p p 7     a7a6      7 . . p p p p p p 7
6 . . . . . . . . 6               6 . p . . . . . . 6               6 p p . . . . . . 6
5 . . . . . . . . 5               5 . . . . . . . . 5               5 . . . . . . . . 5
4 . . . . . . . . 4               4 . . . . P . . . 4               4 . . . P P . . . 4
3 . . . . . . . . 3               3 . . . . . . . . 3               3 . . . . . . . . 3
2 P P P P P P P P 2               2 P P P P . P P P 2               2 P P P . . P P P 2
1 R N B Q K B N R 1               1 R N B Q K B N R 1               1 R N B Q K B N R 1
  a b c d e f g h                   a b c d e f g h                   a b c d e f g h

```

### ScidvsPC: 
[GUI](https://scidvspc.sourceforge.net/) <br>
<img width="671" height="540" alt="image" src="https://github.com/user-attachments/assets/6b0ac722-d7a2-4e9f-9f85-c9bae1874eae" />


## Architecture

```
src/
├── main.cpp              # Entry point, CLI argument parsing
├── position/             # Board representation, move encoding
├── movegen/              # Legal move generation, attack detection
├── eval/                 # Position evaluation
├── search/               # Minimax search
└── game/                 # Game loop, I/O handling
```

### Components

- **Board** — bitboard-based position representation with Zobrist hashing support
- **MoveGen** — pseudo-legal move generation with legality filtering
- **Eval** — material-based evaluation with multiple piece valuation systems
- **Search** — minimax depth-first search
- **Game** — manages the play loop between user and engine

## Roadmap

- [ ] Alpha-beta pruning
- [ ] Iterative deepening
- [ ] Transposition tables
- [ ] Piece-square tables in evaluation
- [ ] Quiescence search
- [ ] UCI protocol support (CuteChess integration)
- [ ] Time management
- [ ] Opening book

## License

MIT
