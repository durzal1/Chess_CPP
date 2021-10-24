//
// Created by zacky on 10/21/2021.
//

#include "moveGenerator.h"

moveGen::moveGen() = default;


moveGen::moveGen(const bitboard &Bitboard, Color color){
    this->bitBoard = Bitboard;
    this->color = color;
}

void moveGen::genAll() {

}

void moveGen::genPawnQuiet() {
    U64 up1;
    if (color == white) up1 = bb::shiftNorth(bitBoard.wpawns) & bitBoard.empty;
    else up1 = bb::shiftSouth(bitBoard.bpawns) & bitBoard.empty;

    U64 up2;
    if (color == white) up2 = bb::shiftNorth(up1) & bitBoard.empty;
    else up2 = bb::shiftSouth(up1) & bitBoard.empty;

    Square target;
    Square from;

    while (up1){
        target = bb::bitscanForward(up1);

        if (color == white){
            from = target - 8;
        }
        else{
            from = target + 8;
        }
        movelist.add(genMove(from, target,QUIET, PAWN));
        up1 = bb::lsbReset(up1);
    }
    while (up2){
        target = bb::bitscanForward(up2);
        if (color == white) from = target - 16;
        else from = target + 16;

        // does not let pieces that have moved, move again
        if (color == white){
            if (from < 16){
                movelist.add(genMove(from, target,QUIET, PAWN));
            }
        }else{
            if (from >= 48){
                movelist.add(genMove(from, target,QUIET, PAWN));
            }
        }
        up2 = bb::lsbReset(up2);
    }
}
void moveGen::genPawnCap() {
    U64 right;
    if (color == white) right = bitBoard.wpawns << 9 & bb::notAFile & bitBoard.allBlack;
    else right = bitBoard.bpawns >> 7 & bb::notAFile & bitBoard.allWhite;

    U64 left;
    if (color == white) left = bitBoard.wpawns << 7 & bb::notHFile & bitBoard.allBlack;
    else left = bitBoard.bpawns >> 9 & bb::notHFile & bitBoard.allWhite;

    Square target;
    Square from;

    while (right){
        target = bb::bitscanForward(right);

        if (color == white) from = target - 9;
        else from = target + 7;

        movelist.add(genMove(from, target,CAPTURE, PAWN));

        right = bb::lsbReset(right);
    }
    while (left){
        target = bb::bitscanForward(left);

        if (color == white) from = target - 7;
        else from = target + 9;

        movelist.add(genMove(from, target,CAPTURE, PAWN));

        left = bb::lsbReset(left);
    }
}

void moveGen::genRook(){
    // bitboard of current color's rook
    U64 rook;

    // all pieces of opposing side
    U64 opp;
    if (color == white){
        opp = bitBoard.allBlack;
        rook = bitBoard.wrooks;
    }
    else{
        opp = bitBoard.allWhite;
        rook = bitBoard.brooks;
    }

    // all occupied squares
    U64 occ = bitBoard.all;

    Square target;
    Square to;

    while (rook){
        target = bb::bitscanForward(rook);
        U64 options = bb::generateRookAttack(target, occ);

        // captures and quiet moves respectively
        U64 captures = options & opp;
        U64 quietMoves = options & bitBoard.empty;

        while(captures){
            to = bb::bitscanForward(captures);
            movelist.add(genMove(target, to,CAPTURE, ROOK));

            captures = bb::lsbReset(captures);
        }

        while (quietMoves){
            to = bb::bitscanForward(quietMoves);
            movelist.add(genMove(target, to,QUIET, ROOK));
            quietMoves = bb::lsbReset(quietMoves);
        }

        rook = bb::lsbReset(rook);
    }
}

void moveGen::genBishop(){
    // bitboard of current color's rook
    U64 bishop;

    // all pieces of opposing side
    U64 opp;
    if (color == white){
        opp = bitBoard.allBlack;
        bishop = bitBoard.wbishops;
    }
    else{
        opp = bitBoard.allWhite;
        bishop = bitBoard.bbishops;
    }

    // all occupied squares
    U64 occ = bitBoard.all;

    Square target;
    Square to;

    while (bishop){
        target = bb::bitscanForward(bishop);
        U64 options = bb::generateBishopAttack(target, occ);

        // captures and quiet moves respectively
        U64 captures = options & opp;
        U64 quietMoves = options & bitBoard.empty;

        while(captures){
            to = bb::bitscanForward(captures);
            movelist.add(genMove(target, to,CAPTURE, BISHOP));

            captures = bb::lsbReset(captures);
        }

        while (quietMoves){
            to = bb::bitscanForward(quietMoves);
            movelist.add(genMove(target, to,QUIET, BISHOP));
            quietMoves = bb::lsbReset(quietMoves);
        }

        bishop = bb::lsbReset(bishop);
    }
}

void moveGen::genQueen(){
    // bitboard of current color's rook
    U64 queen;

    // all pieces of opposing side
    U64 opp;
    if (color == white){
        opp = bitBoard.allBlack;
        queen = bitBoard.wqueens;
    }
    else{
        opp = bitBoard.allWhite;
        queen = bitBoard.bqueens;
    }

    // all occupied squares
    U64 occ = bitBoard.all;

    Square target;
    Square to;

    while (queen){
        target = bb::bitscanForward(queen);
        U64 options = bb::generateBishopAttack(target, occ) | bb::generateRookAttack(target, occ);

        // captures and quiet moves respectively
        U64 captures = options & opp;
        U64 quietMoves = options & bitBoard.empty;

        while(captures){
            to = bb::bitscanForward(captures);
            movelist.add(genMove(target, to,CAPTURE, QUEEN));

            captures = bb::lsbReset(captures);
        }

        while (quietMoves){
            to = bb::bitscanForward(quietMoves);
            movelist.add(genMove(target, to,QUIET, QUEEN));
            quietMoves = bb::lsbReset(quietMoves);
        }

        queen = bb::lsbReset(queen);
    }
}

void moveGen::genKing(){
    // bitboard of current color's rook
    U64 king;

    // all pieces of opposing side
    U64 opp;
    if (color == white){
        opp = bitBoard.allBlack;
        king = bitBoard.wkings;
    }
    else{
        opp = bitBoard.allWhite;
        king = bitBoard.bkings;
    }

    U64 east = king << 1;
    U64 soEa = king >> 7;
    U64 sout = king >> 8;
    U64 soWe = king >> 9;
    U64 west = king >> 1;
    U64 noWe = king << 7;
    U64 nort = king << 8;
    U64 noEa = king << 9;

    // puts it all into a bitmap
    U64 king2 = east | soEa | sout | soWe | west | noWe | nort | noEa;

    // all occupied squares
    U64 occ = bitBoard.all;

    Square target;
    Square from = bb::bitscanForward(king);
    Square to;

    // ensures that moves dont go to the other side of the board
    if (from % 8 == 0) king2 &= bb::notHFile;
    else if (from % 8 == 7) king2 &= bb::notAFile;

    // gets the captures and quiet moves
    U64 attacks = king2 & opp;
    U64 quiet = king2 & bitBoard.empty;

    bb::printBitmap(quiet);
    bb::printBitmap(attacks);

    while (attacks){
        target = bb::bitscanForward(attacks);
        movelist.add(genMoveCap(from, target, CAPTURE, KING, ROOK));
        attacks = bb::lsbReset(attacks);
    }

    while (quiet){
        target = bb::bitscanForward(quiet);
        movelist.add(genMove(from, target, QUIET, KING));
        quiet = bb::lsbReset(quiet);
    }
}

void moveGen::genHorse() {

    // bitboard of current color's horse
    U64 horse;

    // all pieces of opposing side
    U64 opp;
    if (color == white){
        opp = bitBoard.allBlack;
        horse = bitBoard.whorses;
    }
    else{
        opp = bitBoard.allWhite;
        horse = bitBoard.bhorses;
    }


    Square target;
    Square to;

    while (horse){
        target = bb::bitscanForward(horse);

        // temp board of only the current horse being scanned
        U64 temp;
        bb::setBit(temp, target);

        // all options
        U64 noNoEa = temp << 17 & bb::notAFile;
        U64 noEaEa = temp << 10 & bb::notABFile;
        U64 soEaEa = temp >> 6 & bb::notABFile;
        U64 soSoEa = temp >> 15 & bb::notAFile;
        U64 noNoWe = temp << 15 & bb::notHFile;
        U64 noWeWe = temp << 6  & bb::notGHFile;
        U64 soWeWe = temp >> 10 & bb::notGHFile;
        U64 soSoWe = temp >> 17 & bb::notHFile;

        temp = noNoEa | noEaEa | soEaEa | soSoEa | noNoWe | noWeWe | soWeWe | soSoWe;

//      captures and quiet moves respectively
        U64 captures = temp & opp;
        U64 quietMoves = temp & bitBoard.empty;

        bb::printBitmap(captures);
        while(captures){
            to = bb::bitscanForward(captures);
            movelist.add(genMove(target, to,CAPTURE, HORSE));

            captures = bb::lsbReset(captures);
        }

        while (quietMoves){
            to = bb::bitscanForward(quietMoves);
            movelist.add(genMove(target, to,QUIET, HORSE));
            quietMoves = bb::lsbReset(quietMoves);
        }

        horse = bb::lsbReset(horse);
    }
    movelist.printMoveBits();
    bb::printBitmap(bitBoard.all);

    // todo set the captured piece type and test move gen

}
