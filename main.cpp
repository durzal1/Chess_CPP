#include <iostream>
#include "board.h"
#include "ai.h"
#include <chrono>

/*
for zacky
#include <bits/stdc++.h>
  #include <SDL2/SDL_image.h>

*/
/*
for kevin
  #include "SDL_image.h"
*/


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

std::string Default = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
std::string FEN = "rnbqkbnr/ppp1pppp/8/1B1p4/8/4P3/PPPP1PPP/RNBQK1NR b QKqk - 1 1";
int main() {

    // const
    const int posX =450, posY = 30, width = 1000, height = 1000;

//    // initializes SDL
//    SDL_Window* win = NULL;
//    SDL_Renderer* renderer = NULL;
//
//    SDL_Init(SDL_INIT_VIDEO);
//
//    win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);
//    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    board Board = board(width); // win, renderer,
    Board.FENboard(Default);
    auto start = std::chrono::high_resolution_clock::now();

    ai AI = ai(Board, 5, white);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << " moves took " << duration.count() << " ms.";
    //SDL_Delay(90200);
   
    return 0;
} // 4259
