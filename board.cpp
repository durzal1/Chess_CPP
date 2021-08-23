//
// Created by zacky on 8/15/2021.
//


#include "board.h"


board::board( int width) { // SDL_Window* win, SDL_Renderer* renderer1,
//    this->win = win;
//    this->renderer = renderer1;
    this->width = width;

    // interval
    inter = width/ 8;

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

    /*
    for kevin
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
    */

//
//    // adds them to the textures vector
//    textures = {pawnB, horseB, queenB, kingB, rookB, bishopB, pawnW, horseW, queenW, kingW, rookW, bishopW};


    // creates the pieces and board
    this->createPieces();

    /// TESTING POSITIONS
//    BoardLoc{};


    this->createBoard();
//    posMoves("queen", 4,4, "white", BoardLoc, inter, renderer);
}

// inits the pieces in their respective data classes
void board::createPieces() {

    /// black
    // top row
    piece p = piece(0,0,ROOK, black);
    boardArr[0][0] = p;
    IndClass.emplace_back(ROOK);
    PieceLoc[IndClass.size()] = {0,0};
    BoardLoc[{0,0}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][1] = piece(0,1,HORSE, black);
    IndClass.emplace_back(HORSE);
    PieceLoc[IndClass.size()] = {0,1};
    BoardLoc[{0,1}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][2] = piece(0,2,BISHOP, black);
    IndClass.emplace_back(BISHOP);
    PieceLoc[IndClass.size()] = {0,2};
    BoardLoc[{0,2}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][3] = piece(0,3,QUEEN, black);
    IndClass.emplace_back(QUEEN);
    PieceLoc[IndClass.size()] = {0,3};
    BoardLoc[{0,3}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][4] = piece(0,4,KING, black);
    IndClass.emplace_back(KING);
    PieceLoc[IndClass.size()] = {0,4};
    BoardLoc[{0,4}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][5] = piece(0,5,BISHOP, black);
    IndClass.emplace_back(BISHOP);
    PieceLoc[IndClass.size()] = {0,5};
    BoardLoc[{0,5}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][6] = piece(0,6,HORSE, black);
    IndClass.emplace_back(HORSE);
    PieceLoc[IndClass.size()] = {0,6};
    BoardLoc[{0,6}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][7] = piece(0,7,ROOK, black);
    IndClass.emplace_back(ROOK);
    PieceLoc[IndClass.size()] = {0,7};
    BoardLoc[{0,7}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    // pawns
    for (uint64_t i = 0; i < 8; i++){
        IndClass.emplace_back(PAWN);
        boardArr[1][i] = piece(1,i,PAWN, black);
        PieceLoc[IndClass.size()] = {1,i};
        BoardLoc[{1,i}] = IndClass.size();
        blackPieces.insert(IndClass.size());
    }

    /// white
    // bottom row
    boardArr[7][0] = piece(7,0,ROOK, white);
    IndClass.emplace_back(ROOK);
    PieceLoc[IndClass.size()] = {7,0};
    BoardLoc[{7,0}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][1] = piece(7,1,HORSE, white);
    IndClass.emplace_back(HORSE);
    PieceLoc[IndClass.size()] = {7,1};
    BoardLoc[{7,1}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][2] = piece(7,2,BISHOP, white);
    IndClass.emplace_back(BISHOP);
    PieceLoc[IndClass.size()] = {7,2};
    BoardLoc[{7,2}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][3] = piece(7,3,QUEEN, white);
    IndClass.emplace_back(QUEEN);
    PieceLoc[IndClass.size()] = {7,3};
    BoardLoc[{7,3}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][4] = piece(7,4,KING, white);
    IndClass.emplace_back(KING);
    PieceLoc[IndClass.size()] = {7,4};
    BoardLoc[{7,4}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][5] = piece(7,5,BISHOP, white);
    IndClass.emplace_back(BISHOP);
    PieceLoc[IndClass.size()] = {7,5};
    BoardLoc[{7,5}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][6] = piece(7,6,HORSE, white);
    IndClass.emplace_back(HORSE);
    PieceLoc[IndClass.size()] = {7,6} ;
    BoardLoc[{7,6}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][7] = piece(7,7,ROOK, white);
    IndClass.emplace_back(ROOK);
    PieceLoc[IndClass.size()] = {7,7};
    BoardLoc[{7,7}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    // pawns
    for (uint64_t i = 0; i < 8; i++){
        boardArr[6][i] = piece(6,i,PAWN, white);
        IndClass.emplace_back(PAWN);
        PieceLoc[IndClass.size()] = {6,i};
        BoardLoc[{6,i}] = IndClass.size();
        whitePieces.insert(IndClass.size());
    }

}
// create board
void board::createBoard() {
//    // set color to black
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//
//    // Clear the entire screen to black
//    SDL_RenderClear(renderer);
//
//    // iterate through each square and draw it
//    for (int row = 0; row < 8; row++){
//        for (int col = 0; col<8; col++){
//            // if the row and col is even or if the row and col is even
//            if (row % 2 == 0 && col % 2 == 0 || row % 2 == 1 && col % 2 == 1){
//                // make it light
//                SDL_SetRenderDrawColor(renderer, 232,235,239, 255);
//            }
//            else{
//                // make it dark
//                SDL_SetRenderDrawColor(renderer, 125, 135, 150, 255);
//            }
//            SDL_Rect rect{col*inter, row*inter, inter, inter};
//            SDL_RenderFillRect(renderer, &rect);
//
//            // class it will draw (if any)
//            std::string piece;
//            // if theres a piece it adds it
//            if (BoardLoc.find({ row,col }) != BoardLoc.end()) {
//                // get the index
//                int index = BoardLoc[{row,col}];
//
//                // checks what piece it is
//                piece = IndClass[index -1];
//
//                // add extra mandatory character
//                if (index > 16) piece.push_back('W');
//                else piece.push_back('B');
//            }
//
//            // something belongs in the square
//            if (!piece.empty()){
//                // creates the square that will hold the png
//                SDL_Rect pieceRect{col * inter , row* inter , inter, inter};
//
//                // gets index of the texture
//                auto it = std::find(texturesStr.begin(), texturesStr.end(), piece);
//                int index = it - texturesStr.begin();
//
//                // gets the png texture
//                SDL_Texture *texture = textures[index];
//
//                // renders it
//                SDL_RenderCopy(renderer, texture, NULL, &pieceRect);
//            }
//
//        }
//    }
//    // present to screen
//    SDL_RenderPresent(renderer);
}

piece board::move(piece &Piece) {

    // looks to see if a rook got captured
    // if it did it will remove its side's right to castle
    castles.clear();
    if (Piece.captured){
        if (Piece.color == white){
            if (Piece.nextRow == 0 && Piece.nextCol == 4){
                // removes both sides' rights
                blackCastleLeft = false;
                blackCastleRight = false;
                castles.push_back(blackCastleLeft);
                castles.push_back(blackCastleRight);
            }else if (Piece.type == 0 && Piece.nextCol == 0){
                blackCastleLeft = false;
                castles.push_back(blackCastleLeft);
            }
            else if (Piece.type == 0 && Piece.nextCol == 7){
                blackCastleRight = false;
                castles.push_back(blackCastleRight);
            }

        }else{
            if (Piece.nextRow == 7 && Piece.nextCol == 4){
                // removes both sides' rights
                whiteCastleLeft = false;
                whiteCastleRight = false;
                castles.push_back(whiteCastleLeft);
                castles.push_back(whiteCastleRight);
            }else if (Piece.type == 7 && Piece.nextCol == 0){
                whiteCastleLeft = false;
                castles.push_back(whiteCastleLeft);
            }
            else if (Piece.type == 7 && Piece.nextCol == 7){
                whiteCastleRight = false;
                castles.push_back(whiteCastleRight);
            }
        }
    }
    if (Piece.Castle != none) std::cout << 'f';
    // saves the old piece
    piece oldPiece = boardArr[Piece.nextRow][Piece.nextCol];

    // changes the arrBoard
    boardArr[Piece.nextRow][Piece.nextCol] = Piece;

    // makes it empty
    boardArr[Piece.curRow][Piece.curCol] = piece();

    return oldPiece;
}
void board::undoMove(piece &Piece, piece oldPiece) {

    // resets the arrBoard
    boardArr[Piece.nextRow][Piece.nextCol] = Piece;

    // makes it empty
    boardArr[Piece.curRow][Piece.curCol] = piece();
}

