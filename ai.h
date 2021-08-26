//
// Created by zacky on 8/16/2021.
//

#ifndef CHESS_AI_H
#define CHESS_AI_H
#include "board.h"
#include "getPossibleMoves.h"
#include "piece.h"
#include "types.h"
/* zacky

#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
 */
/*
kevin
*/
#include <iostream>
#include <set>
class ai{
private:
    int maxDepth;

    // if check against user
    //bool check = false;

    bool CheckMate = false;
public:
    // constructor (dont know what to put here yet)
    ai(const board& Board, int maxDepth, Color color);


    // main recursive function that gets moves and gets scores with minMax
    // @param Board, this is the Board class that contains all the information of the board
    // @param index, index of the piece
    // @param color, color of the peice (black or white)
    // @param depth, current depth of the recursive search
    // @param Row, this is the row that the piece is currently moving to that we need to update in the Board data classes
    // @param Col, same as former except the column
    // @param captured, checks if piece is captured by its move
    // @param totalMoves, for debugging checks how many moves have occured
    // @param string castle, this is a string that tells if the move is a castle
    void getScores(board Board, int index, std::string color, int depth, int row, int col, bool captured, int &totalMoves, std::string castle) ;

    // function to check if the move will stop the check
    // @return whether it is still check
    bool moveCheck(board b, const piece& Piece, int kingMoves);

    // function that looks at all squares that can attack the king and determines if the piece there can do the attack
    // @return number of pieces that can attack the king (0,1,2)
    int kingAttacks(board Board, piece Piece);

    U64 perft(board b, int depth, bool print, Color color);
};
#endif //CHESS_AI_H
