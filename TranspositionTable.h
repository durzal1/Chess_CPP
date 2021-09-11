//
// Created by Clutc on 9/7/2021.
//

#ifndef CHESS_TRANSPOSITIONTABLE_H
#define CHESS_TRANSPOSITIONTABLE_H
#include "piece.h"
#include "cmath"
#include "array"

// stores what each square is worth (randomly generated at the beginning of the program)
struct zobVal{
    // give a value for each piece that could occupy the square
    U64 wPawn{};
    U64 bPawn{};

    U64 wQueen{};
    U64 bQueen{};

    U64 wBishop{};
    U64 bBishop{};

    U64 wKing{};
    U64 bKing{};

    U64 wHorse{};
    U64 bHorse{};

    U64 wRook{};
    U64 bRook{};

    zobVal();

    // copy constructor
    zobVal(const zobVal& z);

    zobVal& operator=(const zobVal& z);

    // set up the zob values per each square
    static zobVal setup();

    // gets the zobrist key of a board
    U64 getZob(piece boardArr[8][8], zobVal zobVals[8][8]);
};

// used in the universal transposition table to store the data
struct TranspositionTable{
private:

public:
    // the zoborist key used for identification/index purposes
    U64 zoborist;

    // the score of the move
    int score;

    // current depth of the search
    int depth;

    // the best move that leads to this
    piece Move;

    // constructor
    TranspositionTable(U64 zobKey, int score, int depth, const piece& bestMove);

    // copy constructor
    TranspositionTable(const TranspositionTable& b);

    TranspositionTable& operator=(const TranspositionTable& b);


};
#endif //CHESS_TRANSPOSITIONTABLE_H