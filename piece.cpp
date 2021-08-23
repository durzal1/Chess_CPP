//
// Created by zacky on 8/23/2021.
//

#include "piece.h"


piece::piece(row curRow, col curCol, PieceTypes type, Color color) {
    this->curCol = curCol;
    this->curRow = curRow;
    this->type = type;
    this->color = color;
}

piece::piece(const piece &Piece) {
    this->curCol= Piece.curCol;
    this->curRow = Piece.curRow;

    this->type = Piece.type;
    this->color = Piece.color;

    this->nextCol = Piece.nextCol;
    this->nextRow = Piece.nextRow;
}

piece &piece::operator=(const piece &Piece) {
    this->type = Piece.type;
    this->curRow = Piece.curRow;
    this->curCol = Piece.curCol;
    this->color = Piece.color;
    this->nextRow = Piece.nextRow;
    this->nextCol = Piece.nextCol;
    this->Castle = Piece.Castle;
    return *this;
}

piece::piece() {
}






