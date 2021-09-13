//
// Created by Clutc on 9/7/2021.
//

#include "TranspositionTable.h"
#include "random.h"
zobVal::zobVal() = default;


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

zobVal zobVal::setup() {
    auto z = zobVal();

    // generate each value
    z.bPawn = randomint(0,922337204000000000);
    z.wPawn = randomint(0,922337204000000000);

    z.wPawn = randomint(0,922337204000000000);
    z.bPawn = randomint(0,922337204000000000);

    z.wQueen = randomint(0,922337204000000000);
    z.bQueen = randomint(0,922337204000000000);

    z.wBishop = randomint(0,922337204000000000);
    z.bBishop = randomint(0,922337204000000000);

    z.wKing = randomint(0,922337204000000000);
    z.bKing = randomint(0,922337204000000000);

    z.wHorse = randomint(0,922337204000000000);
    z.bHorse = randomint(0,922337204000000000);

    z.wRook = randomint(0,922337204000000000);
    z.bRook = randomint(0,922337204000000000);

    //    std::array<U64, 12> arr {bPawn, wPawn, wQueen, bQueen, wBishop, bBishop, wKing, bKing, wHorse, bHorse, wRook, bRook};

    return z;
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