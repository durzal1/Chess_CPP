//
// Created by zacky on 10/21/2021.
//

#ifndef CHESS_MOVEGENERATOR_H
#define CHESS_MOVEGENERATOR_H
#include "board.h"
#include "moveList.h"
struct moveGen{
private:
    bitboard bitBoard;
    moveList movelist;
public:
    moveGen();

    moveGen(const bitboard &bitBoard);

    /**
     * generates all white quiet moves and updates the moveList
     */
    void genWPawnQuiet();

    void genAll();

};



#endif //CHESS_MOVEGENERATOR_H
