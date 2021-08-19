#include <iostream>
#include "board.h"
#include "ai.h"

/*
for zacky
*/
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
/*
for kevin
 #include "SDL_image.h"
*/

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

    ai AI = ai(Board,4);
    SDL_Delay(90200);
    return 0;
}
