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
#include "evaluate.h"
#include <fstream>
#include <thread>
class ai{
private:
    // time limit
    long long timeLimit;

    // if check against user
    //bool check = false;

public:
    int maxDepth;

    // constructor (dont know what to put here yet)
    ai(const board& Board, int maxDepth, Color color, long long timeLimit);

    // function to check if the move will stop the check
    // @return whether it is still check
    static bool moveCheck(board b, const piece& Piece, int kingMoves);

    // function that checks if the king is in jeopardy and does some other minor things for castling and such
    // @param Board b
    static U64 getKingMoves(board &b, Color color, const piece& moves1, const piece& moves2);

    // function that does the minMax algorithm

    int minMax(board b, int depth, Color color, int alpha, int beta, int &nodes, piece &bestMove,std::chrono::time_point<std::chrono::system_clock> start,std::map<std::pair<std::pair<row, col>, std::pair<row,col>>, piece> &nextMoveList, const std::vector <piece>& moveList, std::map<U64, TranspositionTable> &transpositionTable, piece firstMove);

    // function that looks at all squares that can attack the king and determines if the piece there can do the attack
    // @return number of pieces that can attack the king (0,1,2)
    static int kingAttacks(board Board, const piece& Piece);

    // function to check the amount of moves
    U64 perft(board b, int depth, bool print, Color color);
};
#endif //CHESS_AI_H
