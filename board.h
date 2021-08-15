//
// Created by zacky on 8/15/2021.
//

#ifndef CHESS_CPP_BOARD_H
#define CHESS_CPP_BOARD_H
#include "SDL2/SDL.h"
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>

class board{
private:
    // SDL variables
    SDL_Window* win = NULL;
    SDL_Renderer* renderer = NULL;

    // constants
    int width;

    // images
    SDL_Texture *pawnB = nullptr;
    SDL_Texture *horseB  = nullptr;
    SDL_Texture *queenB  = nullptr;
    SDL_Texture *kingB  = nullptr;
    SDL_Texture *rookB = nullptr;
    SDL_Texture *bishopB  = nullptr;

    SDL_Texture *pawnW  = nullptr;
    SDL_Texture *horseW  = nullptr;
    SDL_Texture *queenW = nullptr;
    SDL_Texture *kingW = nullptr;
    SDL_Texture *rookW= nullptr;
    SDL_Texture *bishopW = nullptr;

    // vector with names of pieces whos index correlate to the next with the textures
    std::vector<std::string> texturesStr {"pawnB", "horseB", "queenB", "kingB", "rookB", "bishopB", "pawnW", "horseW", "queenW", "kingW", "rookW", "bishopW"};

    // vector of textures
    std::vector<SDL_Texture*> textures;

    /// For white pieces
    // map of all pieces (ind, cord<x,y>) (DOES UPDATE IF PIECE DIES)
    std::map<int,std::pair<int,int>> whitePieceLoc;

    // map of all cords (cord<x,y>,ind) (DOES UPDATE IF PIECE DIES)
    // basically the opposite of the former where you give it pos and it gives piece
    // used it for updating board
    std::map<std::pair<int,int>,int> whiteBoardLoc;

    // class of each index (DOES NOT UPDATE IF PIECE DIES)
    std::vector<std::string>whiteIndClass;

    /// For black pieces
    // map of all pieces (ind, cord<x,y>) (DOES UPDATE IF PIECE DIES)
    std::map<int,std::pair<int,int>> blackPieceLoc;

    // class of each index (DOES NOT UPDATE IF PIECE DIES)
    std::vector<std::string>blackIndClass;

    // map of all cords (cord<x,y>,ind) (DOES UPDATE IF PIECE DIES)
    std::map<std::pair<int,int>,int> blackBoardLoc;


public:
    // constructor
    board(SDL_Window* win, SDL_Renderer* renderer1, int width);

    // creates/updates board visually
    void createBoard();

    // inits the pieces in their respective data classes
    void createPieces();
};
#endif //CHESS_CPP_BOARD_H
