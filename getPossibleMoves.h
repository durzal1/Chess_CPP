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
#include "piece.h"
// @returns the all legal moves a piece can do
// @param int, row of the move
// @param int, col of the move
// @param bool, if the move captures another piece
// @param string, either empty or castle location ex. "whiteLeft"
void posMoves(const piece& Piece, board Board, std::vector<piece> &moves, Mode mode); //, SDL_Renderer* renderer

std::vector<piece> allPosMoves(board b, Color color);

std::vector<piece> allCaptures(board b, Color color);

std::vector<piece> noCaptures(board b, Color color);
#endif //CHESS_GETPOSSIBLEMOVES_H
