//
// Created by zacky on 10/21/2021.
//

#include "moveGenerator.h"

moveGen::moveGen() = default;


moveGen::moveGen(const bitboard &Bitboard){
    this->bitBoard = Bitboard;
}

void moveGen::genAll() {

}
void moveGen::genWPawnQuiet() {
    U64 up1 = bb::shiftNorth(bitBoard.wpawns) & bitBoard.empty;
    U64 up2 = bb::shiftNorth(up1) & bitBoard.empty;
    bb::printBitmap(up2);

    // vector of all pieces that can go up 2
    bool arr [8];

    Square target;
    Square from;
    while (up1){
        target = bb::bitscanForward(up1);
        from = target - 8;
        movelist.add(genMove(from, target,QUIET, PAWN));

        // if it can also move 2
        if (from < 16) arr[target % 8] = true;

        up1 = bb::lsbReset(up1);
    }
    while (up2){
        target = bb::bitscanForward(up2);
        from = target - 8;
        if (arr[target % 8]){
            auto it = genMove(from - 8, target,QUIET, PAWN);
            movelist.add(it);
        }
        up2 = bb::lsbReset(up2);
    }
//    movelist.printMoveBits();
}