//
// Created by zacky on 8/16/2021.
//

#ifndef CHESS_AI_H
#define CHESS_AI_H
#include "board.h"
#include "getPossibleMoves.h"

/* zacky

 */
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
/*
kevin
*/
#include <iostream>


class ai{
private:
    int maxDepth;

public:

    // constructor (dont know what to put here yet)
    ai(board Board, int maxDepth);


    // main recursive function that gets moves and gets scores with minMax
    // @param
    void getScores(board Board, int index, std::string color, int depth, int row, int col, bool captured) ;

};
#endif //CHESS_AI_H
