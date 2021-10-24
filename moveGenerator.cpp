//
// Created by zacky on 10/21/2021.
//

#include "moveGenerator.h"

moveGen::moveGen() = default;


moveGen::moveGen(const bitboard &Bitboard, Color color, piece boardarr[64]){
    this->bitBoard = Bitboard;
    this->color = color;

    for (int i = 0; i < 64; i++){
        this->boardArr[i] = boardarr[i];
    }

}

moveList moveGen::genAll() {
    genPawnQuiet();

    genPawnCap();
    genRook();
    genBishop();
    genQueen();
    genKing();
    genHorse();

    bb::printBitmap(attackers);

    return movelist;
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
    U64 oppRight;
    if (color == white){
        right = bitBoard.wpawns << 9 & bb::notAFile & bitBoard.allBlack;
        oppRight = bitBoard.bpawns >> 7 & bb::notAFile;
    }
    else{
        right = bitBoard.bpawns >> 7 & bb::notAFile & bitBoard.allWhite;
        oppRight = bitBoard.wpawns << 9 & bb::notAFile ;
    }

    U64 left;
    U64 oppLeft;
    if (color == white){
        left = bitBoard.wpawns << 7 & bb::notHFile & bitBoard.allBlack;
        oppLeft = bitBoard.bpawns >> 9 & bb::notHFile;
    }
    else{
        left = bitBoard.bpawns >> 9 & bb::notHFile & bitBoard.allWhite;
        oppLeft = bitBoard.wpawns << 7 & bb::notHFile;
    }

    // adds the captures to the captures bitboard
    oppCaptures |= oppLeft;
    oppCaptures |= oppRight;

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
    // bitboard of current and opp color's rook
    U64 rook;
    U64 oppRook;

    // all pieces of opposing and current side
    U64 opp;
    U64 team;

    // this color's king
    U64 curKing;

    U64 oppQueen;
    if (color == white){
        opp = bitBoard.allBlack;
        team = bitBoard.allWhite;
        rook = bitBoard.wrooks;
        oppRook = bitBoard.brooks;
        curKing = bitBoard.wkings;
        oppQueen = bitBoard.bqueens;
    }
    else{
        opp = bitBoard.allWhite;
        team = bitBoard.allBlack;
        rook = bitBoard.brooks;
        oppRook = bitBoard.wrooks;
        curKing = bitBoard.bkings;
        oppQueen = bitBoard.wqueens;
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

    // updates attacks that can be done from king location
    while (curKing){
        target = bb::bitscanForward(curKing);
        U64 options = bb::generateRookAttack(target, occ);

        // captures and quiet moves respectively
        U64 captures = options & opp;

        // adds the captures to the captures bitboard
        attackers |= (captures & oppRook);
        attackers |= (captures & oppQueen);

        curKing = bb::lsbReset(curKing);
    }

    // updates the potential moves of the enemy
    while (oppRook){
        target = bb::bitscanForward(oppRook);
        U64 options = bb::generateRookAttack(target, occ ^ curKing);

        // captures and quiet moves respectively
        U64 captures = options & team;
        U64 quietMoves = options & bitBoard.empty;

        // adds the captures to the captures bitboard
        oppCaptures |= captures;
        oppCaptures |= quietMoves;

        oppRook = bb::lsbReset(oppRook);
    }

}

void moveGen::genBishop(){
    // bitboard of current and opp color's bishop
    U64 bishop;
    U64 oppBishop;

    // all pieces of both sides
    U64 opp;
    U64 team;

    // this color's king
    U64 curKing;

    U64 oppQueen;

    if (color == white){
        opp = bitBoard.allBlack;
        team = bitBoard.allWhite;
        bishop = bitBoard.wbishops;
        oppBishop = bitBoard.bbishops;
        curKing = bitBoard.wkings;
        oppQueen = bitBoard.bqueens;
    }
    else{
        opp = bitBoard.allWhite;
        team = bitBoard.allBlack;
        bishop = bitBoard.bbishops;
        oppBishop = bitBoard.wbishops;
        curKing = bitBoard.bkings;
        oppQueen = bitBoard.wqueens;
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

    // updates attacks that can be done from king location
    while (curKing){
        target = bb::bitscanForward(curKing);
        U64 options = bb::generateBishopAttack(target, occ);

        // captures and quiet moves respectively
        U64 captures = options & opp;
        U64 quietMoves = options & bitBoard.empty;

        // adds the captures to the captures bitboard
        attackers |= (captures & oppBishop);
        attackers |= (captures & oppQueen);

        curKing = bb::lsbReset(curKing);
    }

    while (oppBishop){
        target = bb::bitscanForward(oppBishop);
        U64 options = bb::generateBishopAttack(target, occ ^ curKing);

        // captures and quiet moves respectively
        U64 captures = options & team;
        U64 quietMoves = options & bitBoard.empty;

        // adds the captures to the captures bitboard
        oppCaptures |= captures;
        oppCaptures |= quietMoves;

        oppBishop = bb::lsbReset(oppBishop);
    }

}

void moveGen::genQueen(){
    // bitboard of both color's rook
    U64 queen;
    U64 oppQueen;

    // all pieces of opposing side
    U64 opp;
    U64 team;

    // this color's king
    U64 curKing;

    if (color == white){
        opp = bitBoard.allBlack;
        team = bitBoard.allWhite;

        queen = bitBoard.wqueens;
        oppQueen = bitBoard.bqueens;

        curKing = bitBoard.wkings;
    }
    else{
        opp = bitBoard.allWhite;
        team = bitBoard.allBlack;

        queen = bitBoard.bqueens;
        oppQueen = bitBoard.wqueens;

        curKing = bitBoard.bkings;
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

    while (oppQueen){
        target = bb::bitscanForward(oppQueen);
        U64 options = bb::generateBishopAttack(target, occ ^ curKing) | bb::generateRookAttack(target, occ ^ curKing);

        U64 captures = options & team;
        U64 quietMoves = options & bitBoard.empty;

        // adds the captures to the captures bitboard
        oppCaptures |= captures;
        oppCaptures |= quietMoves;

        oppQueen = bb::lsbReset(oppQueen);
    }


}

void moveGen::genKing(){
    // bitboard of both color's rook
    U64 king;
    U64 oppKing;

    // all pieces of opposing side
    U64 opp;
    U64 team;

    if (color == white){
        team = bitBoard.allWhite;
        opp = bitBoard.allBlack;
        king = bitBoard.wkings;
        oppKing = bitBoard.bkings;
    }
    else{
        team = bitBoard.allBlack;
        opp = bitBoard.allWhite;

        oppKing = bitBoard.wkings;
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

    Square target;
    Square from = bb::bitscanForward(king);

    // ensures that moves dont go to the other side of the board
    if (from % 8 == 0) king2 &= bb::notHFile;
    else if (from % 8 == 7) king2 &= bb::notAFile;

    // gets the captures and quiet moves
    U64 attacks = king2 & opp;
    U64 quiet = king2 & bitBoard.empty;

    while (attacks){
        target = bb::bitscanForward(attacks);
        movelist.add(genMoveCap(from, target, CAPTURE, KING, getCapPiece(target)));
        attacks = bb::lsbReset(attacks);
    }

    while (quiet){
        target = bb::bitscanForward(quiet);
        movelist.add(genMove(from, target, QUIET, KING));
        quiet = bb::lsbReset(quiet);
    }

    /// does the same thing but for opp
    U64 Oeast = oppKing << 1;
    U64 OsoEa = oppKing >> 7;
    U64 Osout = oppKing >> 8;
    U64 OsoWe = oppKing >> 9;
    U64 Owest = oppKing >> 1;
    U64 OnoWe = oppKing << 7;
    U64 Onort = oppKing << 8;
    U64 OnoEa = oppKing << 9;

    // puts it all into a bitmap
    U64 Oking2 = Oeast | OsoEa | Osout | OsoWe | Owest | OnoWe | Onort | OnoEa;

    from = bb::bitscanForward(oppKing);

    // ensures that moves dont go to the other side of the board
    if (from % 8 == 0) Oking2 &= bb::notHFile;
    else if (from % 8 == 7) Oking2 &= bb::notAFile;

    // gets the captures and quiet moves
    U64 Oattacks = Oking2 & team;
    U64 Oquiet = Oking2 & bitBoard.empty;

    oppCaptures |= Oattacks;
    oppCaptures |= Oquiet;

}

void moveGen::genHorse() {

    // bitboard of both color's horse
    U64 horse;
    U64 oppHorse;

    // all pieces of opposing side
    U64 opp;
    U64 team;

    // current king
    U64 curKing;

    if (color == white){
        opp = bitBoard.allBlack;
        team = bitBoard.allWhite;

        horse = bitBoard.whorses;
        oppHorse = bitBoard.bhorses;

        curKing = bitBoard.wkings;
    }
    else{
        opp = bitBoard.allWhite;
        team = bitBoard.allBlack;

        horse = bitBoard.bhorses;
        oppHorse = bitBoard.whorses;

        curKing = bitBoard.bkings;

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

        while(captures){
            to = bb::bitscanForward(captures);
            movelist.add(genMoveCap(target, to,CAPTURE, HORSE, getCapPiece(to)));
            captures = bb::lsbReset(captures);
        }

        while (quietMoves){
            to = bb::bitscanForward(quietMoves);
            movelist.add(genMove(target, to,QUIET, HORSE));
            quietMoves = bb::lsbReset(quietMoves);
        }

        horse = bb::lsbReset(horse);
    }
    // updates attacks that can be done from king location

    // all options
    U64 noNoEa = curKing << 17 & bb::notAFile;
    U64 noEaEa = curKing << 10 & bb::notABFile;
    U64 soEaEa = curKing >> 6 & bb::notABFile;
    U64 soSoEa = curKing >> 15 & bb::notAFile;
    U64 noNoWe = curKing << 15 & bb::notHFile;
    U64 noWeWe = curKing << 6  & bb::notGHFile;
    U64 soWeWe = curKing >> 10 & bb::notGHFile;
    U64 soSoWe = curKing >> 17 & bb::notHFile;

    curKing = noNoEa | noEaEa | soEaEa | soSoEa | noNoWe | noWeWe | soWeWe | soSoWe;

    U64 captures = curKing & opp;
    U64 quietMoves = curKing & bitBoard.empty;

    // adds the captures to the captures bitboard
    attackers |= (captures & oppHorse);

    while (oppHorse){
        target = bb::bitscanForward(oppHorse);

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

        U64 captures = temp & team;
        U64 quietMoves = temp & bitBoard.empty;

        // adds the captures to the captures bitboard
        oppCaptures |= captures;
        oppCaptures |= quietMoves;

        oppHorse = bb::lsbReset(oppHorse);
    }

    // todo try checking boardarr v testing each bb to see which one is faster

}

PieceTypes moveGen::getCapPiece(Square square) {
    return boardArr[square].type;
}
