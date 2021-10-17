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
// @param piece, the piece it is searching the moves for
// @param b, board
// @param moves, all the moves that it found
// @param mode, did not use this
// @param hashMove, the best move, if it finds it, it simply ignores it
void posMoves(const piece& Piece, const board& b, std::vector<piece> &moves, Mode mode, const piece& hasMove, std::vector<piece> &essQueenMoves); //, SDL_Renderer* renderer

void bitBoardMoves();

std::vector<piece> allPosMoves(const board& b, Color color, const piece& hashMove, std::vector<piece> &essQueenMoves, Mode mode);

std::vector<piece> allCaptures(const board& b, Color color);

std::vector<piece> noCaptures(const board& b, Color color);
#endif //CHESS_GETPOSSIBLEMOVES_H
