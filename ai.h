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

class ai{
private:
public:

    // constructor (dont know what to put here yet)
    ai(board Board);


    // main recursive function that gets moves and gets scores with minMax
    // @param
    void getScores(board Board, int index, std::string color, int depth, int row, int col) ;

};
#endif //CHESS_AI_H
