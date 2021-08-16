//
// Created by zacky on 8/16/2021.
//
/*
for zacky

*/

#ifndef CHESS_GETPOSSIBLEMOVES_H
#define CHESS_GETPOSSIBLEMOVES_H
#include <bits/stdc++.h>
#include <SDL2/SDL_image.h>
#include "types.h"
// returns the all legal moves a piece can do
std::vector<std::pair<int, int>> posMoves(std::string Class,int row, int col, std::string color,std::map<std::pair<int,int>,int> BoardLoc, int inter, SDL_Renderer* renderer);

#endif //CHESS_GETPOSSIBLEMOVES_H
