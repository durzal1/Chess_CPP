#include "uci.h"
#include <bits/stdc++.h>

//cmake_minimum_required(VERSION 3.17)
//project(Chess)
//
//set(CMAKE_CXX_STANDARD 14)
//
//set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
//set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
//
//include_directories(${PROJECT_SOURCE_DIR}/include)
//link_directories(${PROJECT_SOURCE_DIR}/lib)
//
//set(SOURCE_FILES main.cpp board.h board.cpp getPossibleMoves.h getPossibleMoves.cpp types.h ai.h ai.cpp)
//add_executable(Chess ${SOURCE_FILES})
//target_link_libraries(Chess mingw32 SDL2main SDL2 SDL2_Image)

int main() {
    std::string fen = "rnbqkbnr/p2pp1pp/8/8/8/2p1p1p1/PP1PPPPP/RNBQKBNR w KQkq - 0 1";
    board Board = board(fen);
    ai AI = ai(Board, 1, Board.playerTurn, 90000);
    AI.perft(Board, 3, true, Board.playerTurn);
//
//    // for random
//    srand(time(NULL));
//
//    uci Uci = uci();
//
//    Uci.mainloop();


//    auto stop = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
//    std::cout << " moves took " << duration.count() << " ms.";

    return 0;
}
