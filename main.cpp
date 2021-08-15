#include <iostream>
#include <SDL2/SDL_image.h>
#include "board.h"
#include <bits/stdc++.h>

int main(int argc, char* argv[]) {

    // const
    const int posX =450, posY = 30, width = 1000, height = 1000;

    // initializes SDL
    SDL_Window* win = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    board Board = board(win, renderer, width);
    Board.createPieces();
    Board.createBoard();
    return 0;
}
