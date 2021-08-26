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
    this->captured = Piece.captured;
    this->capRow = Piece.capRow;
    this->capCol = Piece.capCol;
    return *this;
}

piece::piece() {
    this->type = NONE;
}

std::string piece::toString() {
    std::string uci;

    // the rows have to be subtracted by 8 because they are going up to down instead of down to up
    std::string newRow1 = std::to_string(8-oldRow);
    std::string newRow2 = std::to_string(8-nextRow);

    // col values have to be converted to real characters
    char newCol1 = conversion[oldCol];
    char newCol2 = conversion[nextCol];

    uci.append(newCol1 + newRow1);
    uci.append(newCol2 + newRow2);
    return uci;
}







