//
// Created by zacky on 8/23/2021.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include "types.h"
#include "string"
#include "iostream"
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

    // for pawn piece moves
    // if it has moved twice this value will be its en passant vulnerability
    row rowPassant = -1;
    col colPassant = -1;

    // for removing/adding back castle rights
    // if a rook/king moved this stores that data so it can readd castle rights
    bool leftCastleChanged = false;
    bool rightCastleChanged = false;

    // if it was the other sides castle rights that were changed
    bool oppositeLeftCastle = false;
    bool oppositeRightCastle = false;

    // during a pawn promotion, what type the piece will become
    PieceTypes promotion = NONE;

    // value of a piece
    int Value;

    piece();

    piece(row curRow, col curCol, PieceTypes type, Color color);

    // copy constructor
    piece(const piece& Piece);

    piece& operator=(const piece& Piece);


    /* prints move in uci-output to help with debugging
     * @return string with the output
    */
    std::string toString();
};
#endif //CHESS_PIECE_H
