//
// Created by Clutc on 9/7/2021.
//

#include "TranspositionTable.h"
#include "random.h"
zobVal::zobVal() {
    // generate each value
    this->bPawn = randomint(0,pow(2,63) - 2);
    this->wPawn = randomint(0,pow(2,62) - 2);

    wPawn = randomint(0,pow(2,63) - 2);
    bPawn = randomint(0,pow(2,63) - 2);

    wQueen = randomint(0,pow(2,63) - 2);
    bQueen = randomint(0,pow(2,63) - 2);

    wBishop = randomint(0,pow(2,63) - 2);
    bBishop = randomint(0,pow(2,63) - 2);

    wKing = randomint(0,pow(2,63) - 2);
    bKing = randomint(0,pow(2,63) - 2);

    wHorse = randomint(0,pow(2,63) - 2);
    bHorse = randomint(0,pow(2,63) - 2);

    wRook = randomint(0,pow(2,63) - 2);
    bRook = randomint(0,pow(2,63) - 2);
}

zobVal::zobVal(const zobVal &z) {
    this->wPawn = z.wPawn;
    this->bPawn = z.bPawn;

    this->wBishop = z.wBishop;
    this->bBishop = z.bBishop;

    this->wHorse = z.wHorse;
    this->bHorse = z.bHorse;

    this->wQueen = z.wQueen;
    this->bQueen = z.bQueen;

    this->wKing = z.wKing;
    this->bKing = z.bKing;

    this->wRook = z.wRook;
    this->bRook = z.bRook;
}

zobVal &zobVal::operator=(const zobVal &z) {
    this->wPawn = z.wPawn;
    this->bPawn = z.bPawn;

    this->wBishop = z.wBishop;
    this->bBishop = z.bBishop;

    this->wHorse = z.wHorse;
    this->bHorse = z.bHorse;

    this->wQueen = z.wQueen;
    this->bQueen = z.bQueen;

    this->wKing = z.wKing;
    this->bKing = z.bKing;

    this->wRook = z.wRook;
    this->bRook = z.bRook;

    return *this;
}

U64 zobVal::getZob(piece (*boardArr)[8], zobVal (*zobVals)[8]) {
    U64 zobKey = 0;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            auto square = boardArr[i][j];

            if (square.type != NONE){
                // checks the value of it
                switch (square.type){
                    case ROOK:
                        if (square.color == white){
                            if (zobKey == 0) zobKey = zobVals[i][j].wRook;
                            else zobKey ^= zobVals[i][j].wRook;
                        }else{
                            if (zobKey == 0) zobKey = zobVals[i][j].bRook;
                            else zobKey ^= zobVals[i][j].bRook;
                        }
                        break;

                    case BISHOP:
                        if (square.color == white){
                            if (zobKey == 0) zobKey = zobVals[i][j].wBishop;
                            else zobKey ^= zobVals[i][j].wBishop;
                        }else{
                            if (zobKey == 0) zobKey = zobVals[i][j].bBishop;
                            else zobKey ^= zobVals[i][j].bBishop;
                        }
                        break;

                    case HORSE:
                        if (square.color == white){
                            if (zobKey == 0) zobKey = zobVals[i][j].wHorse;
                            else zobKey ^= zobVals[i][j].wHorse;
                        }else{
                            if (zobKey == 0) zobKey = zobVals[i][j].bHorse;
                            else zobKey ^= zobVals[i][j].bHorse;
                        }
                        break;

                    case QUEEN:
                        if (square.color == white){
                            if (zobKey == 0) zobKey = zobVals[i][j].wQueen;
                            else zobKey ^= zobVals[i][j].wQueen;
                        }else{
                            if (zobKey == 0) zobKey = zobVals[i][j].bQueen;
                            else zobKey ^= zobVals[i][j].bQueen;
                        }
                        break;

                    case KING:
                        if (square.color == white){
                            if (zobKey == 0) zobKey = zobVals[i][j].wKing;
                            else zobKey ^= zobVals[i][j].wKing;
                        }else{
                            if (zobKey == 0) zobKey = zobVals[i][j].bKing;
                            else zobKey ^= zobVals[i][j].bKing;
                        }
                        break;
                    case PAWN:
                        if (square.color == white){
                            if (zobKey == 0) zobKey = zobVals[i][j].wPawn;
                            else zobKey ^= zobVals[i][j].wPawn;
                        }else{
                            if (zobKey == 0) zobKey = zobVals[i][j].bPawn;
                            else zobKey ^= zobVals[i][j].bPawn;
                        }
                        break;
                }
            }
        }
    }
    return zobKey;
}

TranspositionTable::TranspositionTable(U64 zobKey, int score, int depth, const piece& bestMove) {
    this->zoborist = zobKey;
    this->score = score;
    this->depth = depth;
    this->Move = bestMove;
}
TranspositionTable::TranspositionTable(const TranspositionTable &t) {
    this->zoborist = t.zoborist;
    this->score = t.score;
    this->depth = t.depth;
    this->Move = t.Move;
}

TranspositionTable &TranspositionTable::operator=(const TranspositionTable &t) {
    this->zoborist = t.zoborist;
    this->score = t.score;
    this->depth = t.depth;
    this->Move = t.Move;
    return *this;
}
