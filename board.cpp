//
// Created by zacky on 8/15/2021.
//

#include "board.h"
board::board(SDL_Window* win, SDL_Renderer* renderer1, int width) {
    this->win = win;
    this->renderer = renderer1;
    this->width = width;

    /*
    for zacky
    // gets the images
    pawnB = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\pawnb.png");
    horseB  = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\horseb.png");
    queenB  = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\queenb.png");
    kingB  = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\kingb.png");
    rookB = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\rookb.png");;
    bishopB  = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\bishopb.png");

    pawnW  = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\pawnw.png");
    horseW  = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\horsew.png");
    queenW = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\queenw.png");
    kingW = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\kingw.png");
    rookW= IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\rookw.png");
    bishopW = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\bishopw.png");
    */

    pawnW = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\pawnw.png");
    horseW = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\horsew.png");
    queenW = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\queenw.png");
    kingW = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\kingw.png");
    rookW = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\rookw.png");
    bishopW = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\bishopw.png");

    pawnB = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\pawnb.png");
    horseB = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\horseb.png");
    queenB = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\queenb.png");
    kingB = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\kingb.png");
    rookB = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\rookb.png");;
    bishopB = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\bishopb.png");

    // adds them to the textures vector
    textures = {pawnB, horseB, queenB, kingB, rookB, bishopB, pawnW, horseW, queenW, kingW, rookW, bishopW};
}

// inits the pieces in their respective data classes
void board::createPieces() {
    /// black
    // top row
    blackIndClass.emplace_back("rookB");
    blackPieceLoc[blackIndClass.size()] = {0,0};
    blackBoardLoc[{0,0}] = blackIndClass.size();

    blackIndClass.emplace_back("horseB");
    blackPieceLoc[blackIndClass.size()] = {0,1};
    blackBoardLoc[{0,1}] = blackIndClass.size();

    blackIndClass.emplace_back("bishopB");
    blackPieceLoc[blackIndClass.size()] = {0,2};
    blackBoardLoc[{0,2}] = blackIndClass.size();

    blackIndClass.emplace_back("queenB");
    blackPieceLoc[blackIndClass.size()] = {0,3};
    blackBoardLoc[{0,3}] = blackIndClass.size();

    blackIndClass.emplace_back("kingB");
    blackPieceLoc[blackIndClass.size()] = {0,4};
    blackBoardLoc[{0,4}] = blackIndClass.size();

    blackIndClass.emplace_back("bishopB");
    blackPieceLoc[blackIndClass.size()] = {0,5};
    blackBoardLoc[{0,5}] = blackIndClass.size();

    blackIndClass.emplace_back("horseB");
    blackPieceLoc[blackIndClass.size()] = {0,6};
    blackBoardLoc[{0,6}] = blackIndClass.size();

    blackIndClass.emplace_back("rookB");
    blackPieceLoc[blackIndClass.size()] = {0,7};
    blackBoardLoc[{0,7}] = blackIndClass.size();

    // pawns
    for (int i = 0; i < 8; i++){
        blackIndClass.emplace_back("pawnB");
        blackPieceLoc[blackIndClass.size()] = {1,i};
        blackBoardLoc[{1,i}] = blackIndClass.size();
    }

    /// white
    // bottom row
    whiteIndClass.emplace_back("rookW");
    whitePieceLoc[whiteIndClass.size()] = {7,0};
    whiteBoardLoc[{7,0}] = whiteIndClass.size();

    whiteIndClass.emplace_back("horseW");
    whitePieceLoc[whiteIndClass.size()] = {7,1};
    whiteBoardLoc[{7,1}] = whiteIndClass.size();

    whiteIndClass.emplace_back("bishopW");
    whitePieceLoc[whiteIndClass.size()] = {7,2};
    whiteBoardLoc[{7,2}] = whiteIndClass.size();

    whiteIndClass.emplace_back("queenW");
    whitePieceLoc[whiteIndClass.size()] = {7,3};
    whiteBoardLoc[{7,3}] = whiteIndClass.size();

    whiteIndClass.emplace_back("kingW");
    whitePieceLoc[whiteIndClass.size()] = {7,4};
    whiteBoardLoc[{7,4}] = whiteIndClass.size();

    whiteIndClass.emplace_back("bishopW");
    whitePieceLoc[whiteIndClass.size()] = {7,5};
    whiteBoardLoc[{7,5}] = whiteIndClass.size();

    whiteIndClass.emplace_back("horseW");
    whitePieceLoc[ whiteIndClass.size()] = {7,6} ;
    whiteBoardLoc[{7,6}] = whiteIndClass.size();

    whiteIndClass.emplace_back("rookW");
    whitePieceLoc[whiteIndClass.size()] = {7,7};
    whiteBoardLoc[{7,7}] = whiteIndClass.size();

    // pawns
    for (int i = 0; i < 8; i++){
        whiteIndClass.emplace_back("pawnW");
        whitePieceLoc[whiteIndClass.size()] = {6,i};
        whiteBoardLoc[{6,i}] = whiteIndClass.size();
    }

}
// create board
void board::createBoard() {
    // set color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Clear the entire screen to black
    SDL_RenderClear(renderer);

    // interval
    int inter = width/ 8;

    // iterate through each square and draw it
    for (int row = 0; row < 8; row++){
        for (int col = 0; col<8; col++){
            // if the row and col is even or if the row and col is even
            if (row % 2 == 0 && col % 2 == 0 || row % 2 == 1 && col % 2 == 1){
                // make it light
                SDL_SetRenderDrawColor(renderer, 232,235,239, 255);
            }
            else{
                // make it dark
                SDL_SetRenderDrawColor(renderer, 125, 135, 150, 255);
            }
            SDL_Rect rect{col*inter, row*inter, inter, inter};
            SDL_RenderFillRect(renderer, &rect);

            // class it will draw (if any)
            std::string piece;
            // if theres a piece it adds it
            if (blackBoardLoc.find({ row,col }) != blackBoardLoc.end()) {
                // get the index
                int index = blackBoardLoc[{row,col}];

                // checks what piece it is
                piece = blackIndClass[index -1];
            }
            else if (whiteBoardLoc.find({ row,col }) != whiteBoardLoc.end()) {
                // get the index
                int index = whiteBoardLoc[{row,col}];

                // checks what piece it is
                piece = whiteIndClass[index - 1];
            }
            // something belongs in the square
            if (!piece.empty()){
                // creates the square that will hold the png
                SDL_Rect pieceRect{col * inter , row* inter , inter, inter};

                // gets index of the texture
                auto it = std::find(texturesStr.begin(), texturesStr.end(), piece);
                int index = it - texturesStr.begin();

                // gets the png texture
                SDL_Texture *texture = textures[index];

                // renders it
                SDL_RenderCopy(renderer, texture, NULL, &pieceRect);
            }

        }
    }
    // present to screen
    SDL_RenderPresent(renderer);
    SDL_Delay(9005000);

}

