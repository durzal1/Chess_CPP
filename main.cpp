#include "uci.h"

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

    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1\n"

                      ;
    board Board = board(fen);

    ai AI = ai(Board, 1, Board.playerTurn, 90000);

    auto start = std::chrono::high_resolution_clock::now();

//    long long int am = AI.perft(Board, 6, true, Board.playerTurn);
    long long int am = AI.perft2(Board, 6, true, Board.playerTurn);
//    long long int am = AI.testTime(Board, 1, true, Board.playerTurn);



    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    auto du = duration.count();

    std::cout << du << "ms" << std::endl;

    long long int v2 =  am / 1000;
   long double val = v2 / du ;
   std::cout.precision(10);
   std::cout.setf(std::ios::fixed);
   cout << "TOTAL NODES: " << am << endl;
    std::cout << val << "mnps" << std::endl;


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
