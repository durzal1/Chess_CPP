//
// Created by zacky on 8/15/2021.
//

#ifndef CHESS_CPP_BOARD_H
#define CHESS_CPP_BOARD_H

/*
for zacky


#include "SDL2/SDL.h"
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
*/
/*
for kevin
  #include "SDL.h"
#include "SDL_image.h"
*/

#include <iostream>
#include <map>
#include <vector>
#include <unordered_set>
#include "types.h"
#include "piece.h"

class board{
private:
//    // SDL variables
//    SDL_Window* win = NULL;
//    SDL_Renderer* renderer = NULL;
//
    // constants
    int width;

//    // images
//    SDL_Texture *pawnB = nullptr;
//    SDL_Texture *horseB  = nullptr;
//    SDL_Texture *queenB  = nullptr;
//    SDL_Texture *kingB  = nullptr;
//    SDL_Texture *rookB = nullptr;
//    SDL_Texture *bishopB  = nullptr;
//
//    SDL_Texture *pawnW  = nullptr;
//    SDL_Texture *horseW  = nullptr;
//    SDL_Texture *queenW = nullptr;
//    SDL_Texture *kingW = nullptr;
//    SDL_Texture *rookW= nullptr;
//    SDL_Texture *bishopW = nullptr;

//    // vector with names of pieces whos index correlate to the next with the textures
//    std::vector<std::string> texturesStr {"pawnB", "horseB", "queenB", "kingB", "rookB", "bishopB", "pawnW", "horseW", "queenW", "kingW", "rookW", "bishopW"};

//    // vector of textures
//    std::vector<SDL_Texture*> textures;

    // vector of castle bool vars that it has done recently(and will have to undo)
    std::vector<bool> castles;

public:
    // if right has the  right to castle (right rook and king hasnt moved)
    bool whiteCastleRight = true;

    // if right has the  right to castle (left rook and king hasnt moved)
    bool whiteCastleLeft = true;


    // if right has the  right to castle (rightrook hasnt moved)
    bool blackCastleRight = true;

    // if right has the  right to castle (left rook hasnt moved)
    bool blackCastleLeft = true;

    // map of all pieces (ind, cord<x,y>) (DOES UPDATE IF PIECE DIES)
    std::map<int,std::pair<int,int>> PieceLoc;

    // size of each square and their interval
    int inter;

    // map of all cords (cord<x,y>,ind) (DOES UPDATE IF PIECE DIES)
    // basically the opposite of the former where you give it pos and it gives piece
    // used it for updating board
    std::map<std::pair<int,int>,int> BoardLoc;

    // class of each index (DOES NOT UPDATE IF PIECE DIES)
    std::vector<PieceTypes>IndClass;

    // indexes of living white pieces (iterate through this for moves)
    std::unordered_set<int> whitePieces;

    // indexes of living black pieces (iterate through this for moves)
    std::unordered_set<int> blackPieces;

    // array of the board
    piece boardArr[8][8];

    // constructor
    board(int width); // SDL_Window* win, SDL_Renderer* renderer1,

    // creates/updates board visually
    void createBoard();

    // inits the pieces in their respective data classes
    void createPieces();

    // @returns the piece that used to be there
    // does the move
    piece move(piece &Piece);

    // undoes the move
    void undoMove(piece &Piece, piece oldPiece);

};
#endif //CHESS_CPP_BOARD_H
