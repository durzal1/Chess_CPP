#include <iostream>
#include "board.h"
#include "ai.h"
#include <chrono>

/*
for zacky
#include <bits/stdc++.h>

*/
/*
for kevin
  #include "SDL_image.h"
*/
  #include <SDL2/SDL_image.h>

int main(int argc, char* argv[]) {

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
    auto start = std::chrono::high_resolution_clock::now();

    ai AI = ai(Board, 5);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << " moves took " << duration.count() << " ms.";
    //SDL_Delay(90200);
   
    return 0;
} // 4259
