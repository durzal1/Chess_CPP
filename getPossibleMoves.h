//
// Created by zacky on 8/16/2021.
//


#ifndef CHESS_GETPOSSIBLEMOVES_H
#define CHESS_GETPOSSIBLEMOVES_H

#include <vector>
#include <iostream>
#include <map>
#include "types.h"

/*
for zacky
#include <SDL2/SDL_image.h>
*/
/*
for kevin

*/
#include "types.h"
#include "board.h"
// @returns the all legal moves a piece can do
// @param int, row of the move
// @param int, col of the move
// @param bool, if the move captures another piece
// @param string, either empty or castle location ex. "whiteLeft"
std::vector<std::tuple<int, int, bool>> posMoves(std::string Class,int row, int col, std::string color,board Board); //, SDL_Renderer* renderer

#endif //CHESS_GETPOSSIBLEMOVES_H
