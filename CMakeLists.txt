cmake_minimum_required(VERSION 3.31)
project(chaturanga)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/eval)
include_directories(src/movegen)
include_directories(src/position)
include_directories(src/search)
include_directories(src/uci)

add_executable(chaturanga
        src/eval/piecesvalueeval.h
        src/eval/eval.h
        src/movegen/legalmovegen.h
        src/movegen/movegen.h
        src/position/position.cpp
        src/position/position.h
        src/search/minmaxdfs.h
        src/search/search.h
        src/uci/uci.cpp
        src/uci/uci.h
        src/main.cpp
        src/types.h
        dir.txt
        Makefile
        README.md
        src/position/color.h
        src/position/chessman.h
        src/position/square.h
        src/position/move.h
        src/position/piece.h
        src/movegen/movelist.h
        src/movegen/attacks.h
        src/game/chess.h
        src/game/game.h
)

target_include_directories(chess-engine PRIVATE ${CMAKE_SOURCE_DIR}/src)