//
// Created by zacky on 8/16/2021.
//

#ifndef CHESS_AI_H
#define CHESS_AI_H
#include "board.h"
#include "getPossibleMoves.h"
#include "piece.h"
#include "types.h"
#include "moveGenerator.h"
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
#include <algorithm>
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

    int pvSearch(board b, int depth, Color color, int alpha, int beta, int &nodes, piece &bestMove,std::chrono::time_point<std::chrono::system_clock> start, std::map<U64, TranspositionTable> &transpositionTable, piece firstMove);

    // q serach
    int qSearch( board b, int alpha, int beta, Color nextColor, int &nodes);

    // zw search
    int zwSearch(int beta, int depth,  board b, Color nextColor, int &nodes);

    // evaluates the current board
    static int Evaluate(board b, Color nextColor);

    // function that looks at all squares that can attack the king and determines if the piece there can do the attack
    // @return number of pieces that can attack the king (0,1,2)
    static int kingAttacks(board Board, const piece& Piece);

    // function to check the amount of moves
    U64 perft(board b, int depth, bool print, Color color);

    // another testing function
    U64 inline perft2(board b, int depth, bool print, Color color);

    // Purley testing purposes.
    U64 testTime(board b, int depth, bool print, Color color);
};
U64 inline ai::perft2(board b, int depth, bool print, Color color) {

    // gets next color
    Color nextColor;

    if (color == white){
        nextColor = black;
        b.playerTurn = color;
    }
    else{
        nextColor = white;
        b.playerTurn = color;
    }

    U64 nodes = 0;
    if (depth == 0) return 1;

    moveGen gen = moveGen(b.bitBoard, b.playerTurn, b.boardArr);

    moveList movelist = gen.genAll();


    for (int i = 0; i < movelist.getSize(); i++) {

        Move m = movelist.getMove(i);

        if (depth == 1){
            nodes ++;
        }else{
            b.move(m);

            U64 np = perft2(b, depth - 1, false, nextColor);
            b.undoMove(m);

            if (print) {
                movelist.toString(m, np);
            }
            nodes += np;
        }


    }
    return nodes;
}

#endif //CHESS_AI_H
