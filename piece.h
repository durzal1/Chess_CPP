//
// Created by zacky on 8/23/2021.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include "types.h"
class piece{
public:
    // current cords
    col curCol;
    row curRow;

    // type
    PieceTypes type = NONE;

    // for the move, where the move will lead to
    col nextCol;
    row nextRow;

    // color
    Color color;

    // if the move captured another piece
    bool captured = false;

    // if its a castle the location
    castle Castle = none;

    piece();

    piece(col curCol, row curRow, PieceTypes type, Color color);

    // copy constructor
    piece(const piece& Piece);

    piece& operator=(const piece& Piece);

    // checks if a move is legal
    bool moveLegal(int kingMoves);
};
#endif //CHESS_PIECE_H
