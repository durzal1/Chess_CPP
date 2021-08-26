//
// Created by zacky on 8/23/2021.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include "types.h"
#include "string"
class piece{
private:
    // array to convert col nums to A-H uci format
    char conversion[8] {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

public:
    // current cords
    col curCol;
    row curRow;

    // type
    PieceTypes type = NONE;

    // for the move, where the move will lead to
    col nextCol;
    row nextRow;

    // the old cords of the moves(used to undo them)
    row oldRow;
    col oldCol;

    // color
    Color color;

    // if the move captured another piece
    bool captured = false;

    // if its a castle the location
    castle Castle = none;

    // position of the piece killed by en passant
    row capRow = -1;
    col capCol = -1;

    piece();

    piece(col curCol, row curRow, PieceTypes type, Color color);

    // copy constructor
    piece(const piece& Piece);

    piece& operator=(const piece& Piece);


    /* prints move in uci-output to help with debugging
     * @return string with the output
    */
    std::string toString();
};
#endif //CHESS_PIECE_H
