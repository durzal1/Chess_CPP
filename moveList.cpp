//
// Created by zacky on 10/21/2021.
//

#include "moveList.h"
/**
 * adds a move
 * @param move
 */
void moveList::add(Move move) {
    moves[size++] = move;
}

/**
 *
 * @return size
 */
int moveList::getSize() const {
    return size;
}


void moveList::toString(const Move &m, U64 np) {
    std::string uci;

    Square from = getSquareFrom(m);
    Square to = getSquareTo(m);

    int nextRow = to / 8;
    int nextCol = to % 8;

    int oldRow = from / 8;
    int oldCol = from % 8;
    // for castling
//    if (Castle != none){
//        if (Castle == whiteCastleLeft) uci = "e1c1";
//        else if (Castle == whiteCastleRight) uci = "e1g1";
//        else if (Castle == blackCastleLeft) uci = "e8c8";
//        else if (Castle == blackCastleRight) uci = "e8g8";
//    }

    // the rows have to be subtracted by 8 because they are going up to down instead of down to up
    std::string newRow1 = std::to_string(oldRow + 1);
    std::string newRow2 = std::to_string(nextRow + 1);

    // col values have to be converted to real characters
    char newCol1 = conversion[oldCol];
    char newCol2 = conversion[nextCol];

    std::cout << newCol1 << newRow1;
    std::cout << newCol2 << newRow2 << " " << np << std::endl;

//    uci.append(newCol1 + newRow1);
//    uci.append(newCol2 + newRow2);



    // if its a promotion then we add what piece it promotes to
//    if (promotion == QUEEN) uci.push_back('q');
//    else if (promotion == ROOK) uci.push_back('r');
//    else if (promotion == BISHOP) uci.push_back('b');
//    else if (promotion == HORSE) uci.push_back('n');

}
Move genMove(const bb::Square &from, const bb::Square &to, const MoveType&type, const bb::Piece &movingPiece){
    Move m {0};

    setSquareFrom(m, from);
    setSquareTo(m, to);
    setType(m, type);
    setMovingPiece(m, movingPiece);

    return m;
}
Move genMoveCap(const bb::Square &from, const bb::Square &to, const MoveType & type, const bb::Piece &movingPiece,
                    const bb::Piece &capturedPiece){
    Move m {0};

    setSquareFrom(m, from);
    setSquareTo(m, to);
    setType(m, type);
    setMovingPiece(m, movingPiece);
    setCapturedPiece(m, capturedPiece);

    return m;

}
/**
 * prints the bits of the move.
 * Useful for debugging.
 * @param move
 */
void PrintMoveBits(Move move, bool bitInfo) {
    std::cout << " ";
    for (int i = 0; i < 8; i++) {
        std::cout << (bool) ((move >> (31 - i)) & 1UL);
    }
    std::cout << " ";
    for (int i = 0; i < 4; i++) {
        std::cout << (bool) ((move >> (23 - i)) & 1UL);
    }
    std::cout << " ";
    for (int i = 0; i < 4; i++) {
        std::cout << (bool) ((move >> (19 - i)) & 1UL);
    }
    std::cout << " ";
    for (int i = 0; i < 4; i++) {
        std::cout << (bool) ((move >> (15 - i)) & 1UL);
    }
    std::cout << " ";
    for (int i = 0; i < 6; i++) {
        std::cout << (bool) ((move >> (11 - i)) & 1UL);
    }
    std::cout << " ";
    for (int i = 0; i < 6; i++) {
        std::cout << (bool) ((move >> (5 - i)) & 1UL);
    }

    if (bitInfo) {
        std::cout << "\n";
        std::cout << "|        |    |    |    |      |      squareFrom\n"
                     "|        |    |    |    |      +--------------------------\n"
                     "|        |    |    |    |             squareTo\n"
                     "|        |    |    |    +---------------------------------\n"
                     "|        |    |    |                  moving piece\n"
                     "|        |    |    +--------------------------------------\n"
                     "|        |    |                       type information\n"
                     "|        |    +-------------------------------------------\n"
                     "|        |                            captured piece\n"
                     "|        +------------------------------------------------\n"
                     "|                                     score information\n"
                     "+---------------------------------------------------------"
                     << std::endl;
    } else {
        std::cout << std::endl;
    }
}
/**
 * prints the bits of all the moves
 */
void moveList::printMoveBits() {
    for (int i = 0; i < this->size; i++) {
        PrintMoveBits(getMove(i), false);
    }
}

void moveList::reset() {
    std::fill_n(moves, 0, size);
    size = 0;
}
