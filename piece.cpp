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
    this->captured = Piece.captured;

    this->capRow = Piece.capRow;
    this->capCol = Piece.capCol;
    this->Castle = Piece.Castle;
    this->rowPassant = Piece.rowPassant;
    this->colPassant = Piece.colPassant;
    this->leftCastleChanged = Piece.leftCastleChanged;
    this->rightCastleChanged = Piece.rightCastleChanged;
    this->promotion = Piece.promotion;
    this->oppositeLeftCastle = Piece.oppositeLeftCastle;
    this->oppositeRightCastle = Piece.oppositeRightCastle;
    this->oldRow = Piece.oldRow;
    this->oldCol = Piece.oldCol;
    this->Value = Piece.Value;
    this->moveOrdGrad = Piece.moveOrdGrad;
    this->moveType = Piece.moveType;
    this->pastMoves = Piece.pastMoves;
    this->ignoreBest = Piece.ignoreBest;
}

piece &piece::operator=(const piece &Piece) {
    this->pastMoves = Piece.pastMoves;
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
    this->rowPassant = Piece.rowPassant;
    this->colPassant = Piece.colPassant;
    this->leftCastleChanged = Piece.leftCastleChanged;
    this->rightCastleChanged = Piece.rightCastleChanged;
    this->oppositeLeftCastle = Piece.oppositeLeftCastle;
    this->oppositeRightCastle = Piece.oppositeRightCastle;
    this->promotion = Piece.promotion;
    this->oldRow = Piece.oldRow;
    this->oldCol = Piece.oldCol;
    this->Value = Piece.Value;
    this->moveOrdGrad = Piece.moveOrdGrad;
    this->moveType = Piece.moveType;
    this->ignoreBest = Piece.ignoreBest;

    return *this;
}

piece::piece() {
    this->type = NONE;
}

std::string piece::toString() {
    std::string uci;

    // for castling
    if (Castle != none){
        if (Castle == whiteCastleLeft) uci = "e1c1";
        else if (Castle == whiteCastleRight) uci = "e1g1";
        else if (Castle == blackCastleLeft) uci = "e8c8";
        else if (Castle == blackCastleRight) uci = "e8g8";
        return  uci;
    }

    // the rows have to be subtracted by 8 because they are going up to down instead of down to up
    std::string newRow1 = std::to_string(8-oldRow);
    std::string newRow2 = std::to_string(8-nextRow);

    // col values have to be converted to real characters
    char newCol1 = conversion[oldCol];
    char newCol2 = conversion[nextCol];

    uci.append(newCol1 + newRow1);
    uci.append(newCol2 + newRow2);



    // if its a promotion then we add what piece it promotes to
    if (promotion == QUEEN) uci.push_back('q');
    else if (promotion == ROOK) uci.push_back('r');
    else if (promotion == BISHOP) uci.push_back('b');
    else if (promotion == HORSE) uci.push_back('n');

    return uci;
}







