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
/**
 * returns a move
 * @param index
 * @return
 */
Move moveList::getMove(int ind) {
    return moves[ind];
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