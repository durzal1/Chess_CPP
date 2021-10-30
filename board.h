//
// Created by zacky on 8/15/2021.
//

#ifndef CHESS_CPP_BOARD_H
#define CHESS_CPP_BOARD_H

#include "TranspositionTable.h"
#include <iostream>
#include <map>
#include <vector>
#include <unordered_set>
#include "types.h"
#include "piece.h"
#include "bitBoard.h"
typedef uint32_t Move;

class board{
private:

//    // SDL variables
//    SDL_Window* win = NULL;
//    SDL_Renderer* renderer = NULL;
//

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

    // vector of castle string vars that it has done recently(and will have to undo)
    std::vector<castle> castles;

    // all constant values that we will need to evaluate the board and piece values
    const int P = 100;
    const int N = 320;
    const int B = 330;
    const int R = 500;
    const int Q = 900;
    const int K = 20000;

    // map with all the hash moves
protected:
    std::map<U64, piece> hashMoves;

public:
    // all bit boards that will be used
    bitboard bitBoard = bitboard();

    // to get zobrist keys in the future
    zobVal zobKeys = zobVal();

    // the zoborist values of each square in the boardArray
    zobVal zobVals[8][8];

    // we put all these values in a hash map to make it easier to call
    std::map<PieceTypes,int> getVal = {
            {PAWN,P},
            {HORSE,N},
            {BISHOP,B},
            {ROOK,R},
            {QUEEN,Q},
            {KING,K},
            };

    // converts letters to numbers for the col
    std::map<char, int> conversion;

    // secondary check if the user can do a castle on either direction
    bool castleRight = false;
    bool castleLeft = false;


    // amount of castles (useful for perft)
    int amountCastles = 0;

    // all castle rights are false by default
    // if right has the  right to castle (right rook and king hasnt moved)
    bool WhiteCastleRight = false;

    // if right has the  right to castle (left rook and king hasnt moved)
    bool WhiteCastleLeft = false;


    // if right has the  right to castle (rightrook hasnt moved)
    bool BlackCastleRight = false;

    // if right has the  right to castle (left rook hasnt moved)
    bool BlackCastleLeft = false;

    // full turns that have been made the entire game
    int fullTurns = 0;

    // half turns that have been made since last time a peice was captured or pawn moved
    int halfTurns = 0;

    // size of each square and their interval
    int inter;

    // array of the board
    piece boardArr[64];

    // whos turn it is
    Color playerTurn = white;

    // vector of en passent moves
    std::vector<std::pair<row, col>> passentMoves;

    // constructor
    board(const std::string&); // SDL_Window* win, SDL_Renderer* renderer1,

    board();

    // copy constructor
    board(const board& b);

    board& operator=(const board& b);

    // creates/updates board visually
    void createBoard();

    void setBitset();

    // inits the pieces in their respective data classes
    static void createPieces();

    // @returns the piece that used to be there
    // does the move
    Move move(Move m);

    // undoes the move
    void undoMove(piece &Piece, const piece& oldPiece);

    // create board from FEN string
    //@param FEN string
    void FENboard(std::string FEN);

    // prints screen to cmd
    void print();

};
#endif //CHESS_CPP_BOARD_H
