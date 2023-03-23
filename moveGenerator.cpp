//
// Created by zacky on 10/21/2021.
//

#include "moveGenerator.h"

moveGen::moveGen() = default;


moveGen::moveGen(const bitboard &Bitboard, Color color,   std::pair<PieceTypes, Color> boardarr[64]){
    this->bitBoard = Bitboard;
    this->color = color;

    for (int i = 0; i < 64; i++){
        this->boardArr[i] = boardarr[i];
    }

}
//void moveGen::genChecks() {
//    /// pawns
//    U64 oppRight;
//    if (color == white){
//        oppRight = ((bitBoard.bpawns >> 7 & bb::notAFile) & bitBoard.wkings) << 7;
//    }
//    else{
//        oppRight = ((bitBoard.wpawns << 9 & bb::notAFile) & bitBoard.bkings) >> 9 ;
//    }
//
//    U64 oppLeft;
//    if (color == white){
//        oppLeft = ((bitBoard.bpawns >> 9 & bb::notHFile) & bitBoard.wkings) << 9 ;
//    }
//    else{
//        oppLeft = ((bitBoard.wpawns << 7 & bb::notHFile) & bitBoard.bkings) >> 7;
//    }
//
//    // adds the captures to the captures bitboard
//    attackers |= oppLeft;
//    attackers |= oppRight;
//
//    // pawn oppCaptures
//    if (color == white){
//        oppRight = bitBoard.bpawns >> 7 & bb::notAFile;
//    }
//    else{
//        oppRight = bitBoard.wpawns << 9 & bb::notAFile ;
//    }
//
//    if (color == white){
//        oppLeft = bitBoard.bpawns >> 9 & bb::notHFile;
//    }
//    else{
//        oppLeft = bitBoard.wpawns << 7 & bb::notHFile;
//    }
//
//    // adds the captures to the captures bitboard
//    oppCaptures |= oppLeft;
//    oppCaptures |= oppRight;
//
//    /// rooks
//
//    // bitboard of current and opp color's rook
//    U64 rook;
//    U64 oppRook;
//
//    // all pieces of opposing and current side
//    U64 opp;
//    U64 team;
//
//    // this color's king
//    U64 curKing;
//
//    U64 oppQueen;
//    if (color == white){
//        team = bitBoard.allWhite;
//        opp = bitBoard.allBlack;
//        oppRook = bitBoard.brooks;
//        curKing = bitBoard.wkings;
//        oppQueen = bitBoard.bqueens;
//    }
//    else{
//        opp = bitBoard.allWhite;
//        team = bitBoard.allBlack;
//        rook = bitBoard.brooks;
//        oppRook = bitBoard.wrooks;
//        curKing = bitBoard.bkings;
//        oppQueen = bitBoard.wqueens;
//    }
//
//    // all occupied squares
//    U64 occ = bitBoard.all;
//
//    Square target;
//    Square to;
//
//    // updates attacks that can be done from king location
//    while (curKing){
//        target = bb::bitscanForward(curKing);
//        U64 options = bb::generateRookAttack(target, occ);
//
//        kingSliding |= options;
//
//        // captures and quiet moves respectively
//        U64 captures = options & opp;
//
//        // adds the captures to the captures bitboard
//        attackers |= (captures & oppRook);
//        attackers |= (captures & oppQueen);
//
//        curKing = bb::lsbReset(curKing);
//    }
//
//    // updates the potential moves of the enemy
//    while (oppRook){
//        target = bb::bitscanForward(oppRook);
//        U64 options = bb::generateRookAttack(target, occ ^ curKing);
//
//        // adds the captures to the captures bitboard
//        oppCaptures |= options;
//
//        oppRook = bb::lsbReset(oppRook);
//    }
//    /// bishops
//
//    // bitboard of current and opp color's bishop
//    U64 bishop;
//    U64 oppBishop;
//
//    if (color == white){
//        opp = bitBoard.allBlack;
//        team = bitBoard.allWhite;
//        bishop = bitBoard.wbishops;
//        oppBishop = bitBoard.bbishops;
//        curKing = bitBoard.wkings;
//        oppQueen = bitBoard.bqueens;
//    }
//    else{
//        opp = bitBoard.allWhite;
//        team = bitBoard.allBlack;
//        bishop = bitBoard.bbishops;
//        oppBishop = bitBoard.wbishops;
//        curKing = bitBoard.bkings;
//        oppQueen = bitBoard.wqueens;
//    }
//
//    // all occupied squares
//    occ = bitBoard.all;
//
//    while (curKing){
//        target = bb::bitscanForward(curKing);
//        U64 options = bb::generateBishopAttack(target, occ);
//
//        kingSliding |= options;
//
//        // captures and quiet moves respectively
//        U64 captures = options & opp;
//        U64 quietMoves = options & bitBoard.empty;
//
//        // adds the captures to the captures bitboard
//        attackers |= (captures & oppBishop);
//        attackers |= (captures & oppQueen);
//
//        curKing = bb::lsbReset(curKing);
//    }
//
//    while (oppBishop){
//        target = bb::bitscanForward(oppBishop);
//        U64 options = bb::generateBishopAttack(target, occ ^ curKing);
//
//        // adds the captures to the captures bitboard
//        oppCaptures |= options;
//
//        oppBishop = bb::lsbReset(oppBishop);
//    }
//    /// Queen
//
//    if (color == white){
//        opp = bitBoard.allBlack;
//        team = bitBoard.allWhite;
//        rook = bitBoard.wrooks;
//        oppRook = bitBoard.brooks;
//        curKing = bitBoard.wkings;
//        oppQueen = bitBoard.bqueens;
//    }
//    else{
//        opp = bitBoard.allWhite;
//        team = bitBoard.allBlack;
//        rook = bitBoard.brooks;
//        oppRook = bitBoard.wrooks;
//        curKing = bitBoard.bkings;
//        oppQueen = bitBoard.wqueens;
//    }
//
//    while (oppQueen){
//        target = bb::bitscanForward(oppQueen);
//        U64 options = bb::generateBishopAttack(target, occ ^ curKing) | bb::generateRookAttack(target, occ ^ curKing);
//
//        U64 captures = options & team;
//        U64 quietMoves = options & bitBoard.empty;
//
//        // adds the captures to the captures bitboard
//        oppCaptures |= options;
//
//        oppQueen = bb::lsbReset(oppQueen);
//    }
//
//    /// king
//
//    // bitboard of both color's rook
//    U64 king;
//    U64 oppKing;
//
//    // all pieces of opposing side
//    if (color == white){
//        team = bitBoard.allWhite;
//        opp = bitBoard.allBlack;
//        king = bitBoard.wkings;
//        oppKing = bitBoard.bkings;
//    }
//    else{
//        team = bitBoard.allBlack;
//        opp = bitBoard.allWhite;
//
//        oppKing = bitBoard.wkings;
//        king = bitBoard.bkings;
//    }
//
//    while (curKing){
//        target = bb::bitscanForward(curKing);
//        U64 options = bb::generateBishopAttack(target, occ);
//
//        // captures and quiet moves respectively
//        U64 captures = options & opp;
//
//        // adds the captures to the captures bitboard
//        attackers |= (captures & oppBishop);
//        attackers |= (captures & oppQueen);
//
//        curKing = bb::lsbReset(curKing);
//    }
//
//
//    // does the same thing but for opp
//    U64 Oeast = oppKing << 1;
//    U64 OsoEa = oppKing >> 7;
//    U64 Osout = oppKing >> 8;
//    U64 OsoWe = oppKing >> 9;
//    U64 Owest = oppKing >> 1;
//    U64 OnoWe = oppKing << 7;
//    U64 Onort = oppKing << 8;
//    U64 OnoEa = oppKing << 9;
//
//    // puts it all into a bitmap
//    U64 Oking2 = Oeast | OsoEa | Osout | OsoWe | Owest | OnoWe | Onort | OnoEa;
//
//    auto from = bb::bitscanForward(oppKing);
//
//    // ensures that moves dont go to the other side of the board
//    if (from % 8 == 0) Oking2 &= bb::notHFile;
//    else if (from % 8 == 7) Oking2 &= bb::notAFile;
//
//    // gets the captures and quiet moves
//    U64 Oattacks = Oking2 & team;
//    U64 Oquiet = Oking2 & bitBoard.empty;
//
//    oppCaptures |= Oattacks;
//    oppCaptures |= Oquiet;
//
//    /// horses
//
//    // bitboard of both color's horse
//    U64 horse;
//    U64 oppHorse;
//
//    if (color == white){
//        opp = bitBoard.allBlack;
//        team = bitBoard.allWhite;
//
//        horse = bitBoard.whorses;
//        oppHorse = bitBoard.bhorses;
//
//        curKing = bitBoard.wkings;
//    }
//    else{
//        opp = bitBoard.allWhite;
//        team = bitBoard.allBlack;
//
//        horse = bitBoard.bhorses;
//        oppHorse = bitBoard.whorses;
//
//        curKing = bitBoard.bkings;
//
//    }
//
//
//    // updates attacks that can be done from king location
//
//    // all options
//    U64 noNoEa = curKing << 17 & bb::notAFile;
//    U64 noEaEa = curKing << 10 & bb::notABFile;
//    U64 soEaEa = curKing >> 6 & bb::notABFile;
//    U64 soSoEa = curKing >> 15 & bb::notAFile;
//    U64 noNoWe = curKing << 15 & bb::notHFile;
//    U64 noWeWe = curKing << 6  & bb::notGHFile;
//    U64 soWeWe = curKing >> 10 & bb::notGHFile;
//    U64 soSoWe = curKing >> 17 & bb::notHFile;
//
//    curKing = noNoEa | noEaEa | soEaEa | soSoEa | noNoWe | noWeWe | soWeWe | soSoWe;
//
//    U64 captures = curKing & opp;
//
//    // adds the captures to the captures bitboard
//    attackers |= (captures & oppHorse);
//
//    while (oppHorse){
//        target = bb::bitscanForward(oppHorse);
//
//        // temp board of only the current horse being scanned
//        U64 temp;
//        bb::setBit(temp, target);
//
//        // all options
//        U64 noNoEa = temp << 17 & bb::notAFile;
//        U64 noEaEa = temp << 10 & bb::notABFile;
//        U64 soEaEa = temp >> 6 & bb::notABFile;
//        U64 soSoEa = temp >> 15 & bb::notAFile;
//        U64 noNoWe = temp << 15 & bb::notHFile;
//        U64 noWeWe = temp << 6  & bb::notGHFile;
//        U64 soWeWe = temp >> 10 & bb::notGHFile;
//        U64 soSoWe = temp >> 17 & bb::notHFile;
//
//        temp = noNoEa | noEaEa | soEaEa | soSoEa | noNoWe | noWeWe | soWeWe | soSoWe;
//
//
//        // adds the captures to the captures bitboard
//        oppCaptures |= temp;
//
//        oppHorse = bb::lsbReset(oppHorse);
//    }
//
//    // bitboard of opponents sliding moves
//    if (color == white){
//        oppBishop = bitBoard.bbishops;
//        oppRook= bitBoard.brooks;
//        oppQueen= bitBoard.bqueens;
//        king = bitBoard.wkings;
//    }
//    else{
//        oppBishop = bitBoard.wbishops;
//        oppRook= bitBoard.wrooks;
//        oppQueen= bitBoard.wqueens;
//        king = bitBoard.bkings;
//    }
//    while (oppBishop){
//        target = bb::bitscanForward(oppBishop);
//        U64 options = bb::generateBishopAttack(target, occ);
//        U64 checkKing = bb::generateBishopAttack(target, 0ULL);
//
//        if ((checkKing & king) == 0ULL){
//            oppBishop = bb::lsbReset(oppBishop);
//            continue;
//        }
//
//        // captures
//        captures = options & team;
//
//        // adds the captures to the opp sliding bitboard
//        oppSliding |= captures;
//
//        oppBishop = bb::lsbReset(oppBishop);
//    }
//
//    while (oppRook){
//        target = bb::bitscanForward(oppRook);
//        U64 options = bb::generateRookAttack(target, occ);
//        U64 checkKing = bb::generateRookAttack(target, 0ULL);
//
//        if ((checkKing & king) == 0ULL){
//            oppRook = bb::lsbReset(oppRook);
//            continue;
//        }
//
//        // captures
//        captures = options & team;
//
//        // adds the captures to the opp sliding bitboard
//        oppSliding |= captures;
//
//        oppRook = bb::lsbReset(oppRook);
//    }
//
//    while (oppQueen){
//        target = bb::bitscanForward(oppQueen);
//        U64 options = bb::generateBishopAttack(target, occ) | bb::generateRookAttack(target, occ);
//        U64 checkKing = bb::generateBishopAttack(target, 0ULL) | bb::generateRookAttack(target, 0ULL);
//
//        if ((checkKing & king) == 0ULL){
//            oppQueen = bb::lsbReset(oppQueen);
//            break;
//        }
//
//        // captures
//        captures = options & team;
//
//        // adds the captures to the opp sliding bitboard
//        oppSliding |= captures;
//
//        oppQueen = bb::lsbReset(oppQueen);
//    }
//
//
//}
//void moveGen::getPinnedMoves() {
//    int indKing;
//    U64 king;
//    U64 opp;
//    if (color == white){
//        indKing = bb::bitscanForward(bitBoard.wkings);
//        king = bitBoard.wkings;
//        opp = bitBoard.allBlack;
//    }else{
//        indKing = bb::bitscanForward(bitBoard.bkings);
//        king = bitBoard.bkings;
//        opp = bitBoard.allWhite;
//    }
//    pinned = oppSliding & kingSliding;
//
//    // temp bitboard for pinned pieces
//    U64 tempPinned = pinned;
//
//    while (tempPinned){
//        int checksquare = bb::bitscanForward(tempPinned);
//
//        int jKing = indKing % 8;
//        int iKing = (indKing - jKing) / 8;
//
//        int jAtt = checksquare % 8;
//        int iAtt = (checksquare - jAtt) / 8;
//
//        // pinned move and move pinner
//        U64 pinnedMoves = 0ULL;
//        int movePinner;
//
//        // direction
//        bb::Directions direction = bb::dirBetTwo(jKing, iKing, jAtt, iAtt);
//        bb::Directions oppDir = bb::oppDirection(direction);
//
//        // makes sure pieces only go where they're supposed to
//        bb::Directions typeDir = bb::typeDirection(direction);
//
//        // type of moving piece
//        PieceTypes moving = boardArr[checksquare].first;
//
//        // bishop can only diag and rook can only non-diag and horse will never have a move
//        if ((typeDir == bb::DIAGONAL && moving == ROOK) || (typeDir == bb::NON_DIAGONAL && moving == BISHOP) || moving == HORSE) break;
//
//
//        pinnedMoves |= bb::generateSlidingAttacks(checksquare, direction, bitBoard.all);
//        pinnedMoves |= bb::generateSlidingAttacks(checksquare, oppDir, bitBoard.all);
//
//        // remove our king
//        pinnedMoves ^= king;
//        movePinner = bb::bitscanForward(pinnedMoves & opp);
//
//        if (moving == PAWN && typeDir == bb::DIAGONAL){
//            pinPawnCap(checksquare, movePinner);
//            break;
//        }
//        else if (moving == PAWN && typeDir == bb::NON_DIAGONAL) break;
//
//        // adds all the moves
//        while (pinnedMoves){
//            int move = bb::bitscanForward(pinnedMoves);
//
//            if (move == movePinner){
//                // capture
//                movelist.add(genMoveCap(checksquare, move, CAPTURE, moving, boardArr[move].first));
//
//            }
//            else{
//                // quiet
//                movelist.add(genMove(checksquare, move, QUIET, moving));
//            }
//
//            pinnedMoves = bb::lsbReset(pinnedMoves);
//
//        }
//
//        tempPinned = bb::lsbReset(tempPinned);
//
//    }
//
//
//}
moveList moveGen::genAll() {
//    // gets number of ways check is made
//    genChecks();
//
//    // moves for pinned pieces
//    getPinnedMoves();
//
//    // always needed
//    genKing();

    int numChecks = bb::bitCount(attackers);

    if (numChecks > 1){
        // only returns king moves since 2+ checks
        return movelist;
    }
    else if (numChecks == 1){

        //// todo fix this with the new bitboard
//        // can only capture the attacking piece
//        capMask = attackers;
//
//        auto checksquare = bb::bitscanForward(attackers);
//
//        // king being targeted
//        U64 king;
//
//        if (color == white) king = bitBoard.wkings;
//        else king = bitBoard.bkings;
//
//        auto indKing = bb::bitscanForward(king);
//
//        // if its not slider then no push mask
//        if (boardArr[checksquare].first == QUEEN || boardArr[checksquare].first == BISHOP || boardArr[checksquare].first == ROOK){
//            // determines direction (don't try to understand how)
//            int jKing = indKing % 8;
//            int iKing = (indKing - jKing) / 8;
//
//            int jAtt = checksquare % 8;
//            int iAtt = (checksquare - jAtt) / 8;
//
//            // direction
//            bb::Directions direction = bb::dirBetTwo(jKing, iKing, jAtt, iAtt);
//
//            moveMask = (bb::generateSlidingAttacks(indKing, direction, attackers)) ^ attackers;
//
//        }
//
//        return movelist;
    }

    // generates all moves
    genPawnQuiet();
    genPawnCap();
    genHorse();
    genRook();
    genBishop();
    genQueen();

    // todo perft and do the actual move
    return movelist;
}
void moveGen::pinPawnCap(int piece, int pinningPiece) {
    U64 board = 0ULL;
    bb::setBit(board, piece);

    U64 right;
    if (color == white){
        right = board << 9 & bb::notAFile & bitBoard.bit_boards[color];
    }
    else{
        right = board >> 7 & bb::notAFile & bitBoard.bit_boards[color];
    }

    U64 left;
    if (color == white){
        left = board << 7 & bb::notHFile &  bitBoard.bit_boards[color];
    }
    else{
        left = board >> 9 & bb::notHFile &  bitBoard.bit_boards[color];
    }


    Square target;
    Square from;

    // adds the capMask
    right &= capMask;
    left  &= capMask;

    while (right){
        target = bb::bitscanForward(right);

        if (target != pinningPiece){
            break;
        }

        if (color == white) from = target - 9;
        else from = target + 7;

        movelist.add(genMoveCap(from, target,CAPTURE, PAWN, boardArr[target].first));

        right = bb::lsbReset(right);
    }
    while (left){
        target = bb::bitscanForward(left);

        if (target != pinningPiece){
            break;
        }

        if (color == white) from = target - 7;
        else from = target + 9;

        movelist.add(genMoveCap(from, target,CAPTURE, PAWN, boardArr[target].first));

        left = bb::lsbReset(left);
    }
}

void moveGen::genPawnQuiet() {

    U64 all = 0, wpawns = bitBoard.bit_boards[PAWN] & bitBoard.bit_boards[white];
    U64 bpawns = bitBoard.bit_boards[PAWN] & bitBoard.bit_boards[black];

    for (int i = 0; i < 8; i++){
        U64 bo = bitBoard.bit_boards[i];
        all |= bo;
    }
    U64 empty = ~all;

    U64 up1;
    if (color == white) up1 = bb::shiftNorth(wpawns) & empty;
    else up1 = bb::shiftSouth(bpawns) & empty;

    U64 up2;
    if (color == white) up2 = bb::shiftNorth(up1) & empty;
    else up2 = bb::shiftSouth(up1) & empty;

    Square target;
    Square from;

    // adds moveMask
    up1 &= moveMask;
    up2 &= moveMask;

    while (up1){
        target = bb::bitscanForward(up1);


        if (color == white){
            from = target - 8;
        }
        else{
            from = target + 8;
        }
        // if pinned we skip since moves have been calculated
        if (bb::getBit(pinned, from)){
            up1 = bb::lsbReset(up1);
            continue;
        }

        movelist.add(genMove(from, target,QUIET, PAWN));
        up1 = bb::lsbReset(up1);
    }
    while (up2){
        target = bb::bitscanForward(up2);

        if (color == white) from = target - 16;
        else from = target + 16;

        // if pinned we skip since moves have been calculated
        if (bb::getBit(pinned, from)){
            up2 = bb::lsbReset(up2);
            continue;
        }

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


    U64 all = 0ULL, wpawns = bitBoard.bit_boards[PAWN] & bitBoard.bit_boards[white];
    U64 bpawns = bitBoard.bit_boards[PAWN] & bitBoard.bit_boards[black];

    for (int i = 0; i < 8; i++){
        all |= bitBoard.bit_boards[i];
    }
    U64 empty = ~all;

    U64 right;
    if (color == white){
        right = wpawns << 9 & bb::notAFile & bitBoard.bit_boards[black];
    }
    else{
        right = bpawns >> 7 & bb::notAFile & bitBoard.bit_boards[white];
    }

    U64 left;
    if (color == white){
        left = wpawns << 7 & bb::notHFile & bitBoard.bit_boards[black];
    }
    else{
        left = bpawns >> 9 & bb::notHFile & bitBoard.bit_boards[white];
    }


    Square target;
    Square from;

    // adds the capMask
    right &= capMask;
    left  &= capMask;

    while (right){
        target = bb::bitscanForward(right);

        if (color == white) from = target - 9;
        else from = target + 7;

        // if pinned we skip since moves have been calculated
        if (bb::getBit(pinned, from)){
            right = bb::lsbReset(right);
            continue;
        }

        movelist.add(genMoveCap(from, target,CAPTURE, PAWN, boardArr[target].first));

        right = bb::lsbReset(right);
    }
    while (left){
        target = bb::bitscanForward(left);

        if (color == white) from = target - 7;
        else from = target + 9;

        // if pinned we skip since moves have been calculated
        if (bb::getBit(pinned, from)){
            left = bb::lsbReset(left);
            continue;
        }

        movelist.add(genMoveCap(from, target,CAPTURE, PAWN, boardArr[target].first));

        left = bb::lsbReset(left);
    }
}

void moveGen::genRook(){


    U64 all = 0ULL, wrooks = bitBoard.bit_boards[ROOK] & bitBoard.bit_boards[white];
    U64 brooks = bitBoard.bit_boards[ROOK] & bitBoard.bit_boards[black];

    for (int i = 0; i < 8; i++){
        all |= bitBoard.bit_boards[i];
    }
    U64 empty = ~all;

    // bitboard of current
    U64 rook;

    // all pieces of opposing and current side
    U64 opp;

    if (color == white){
        opp = bitBoard.bit_boards[black];
        rook = wrooks;
    }
    else{
        opp = bitBoard.bit_boards[white];
        rook = brooks;
    }

    // all occupied squares
    U64 occ = all;

    Square target;
    Square to;

    while (rook){
        target = bb::bitscanForward(rook);

        // if pinned we skip since moves have been calculated
        if (bb::getBit(pinned, target)){
            rook = bb::lsbReset(rook);
            continue;
        }

        U64 options = bb::generateRookAttack(target, occ);

        // captures and quiet moves respectively
        U64 captures = options & opp;
        U64 quietMoves = options & empty;

        // adds masks
        captures &= capMask;
        quietMoves &= moveMask;

        while(captures){
            to = bb::bitscanForward(captures);
            movelist.add(genMoveCap(target, to,CAPTURE, ROOK, boardArr[to].first));

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
        opp = bitBoard.bit_boards[black];
        team = bitBoard.bit_boards[white];
    }
    else{
        opp = bitBoard.bit_boards[white];
        team = bitBoard.bit_boards[black];
    }

    bishop = bitBoard.bit_boards[BISHOP] & team;
    oppBishop = bitBoard.bit_boards[BISHOP] & opp;
    curKing =  bitBoard.bit_boards[KING] & team;
    oppQueen = bitBoard.bit_boards[QUEEN] & opp;


    // all occupied squares
    U64 occ = 0ULL;

    for (int i = 0; i < 8; i++){
        occ |= bitBoard.bit_boards[i];
    }

    U64 empty = ~occ;

    Square target;
    Square to;

    while (bishop){
        target = bb::bitscanForward(bishop);

        // if pinned we skip since moves have been calculated
        if (bb::getBit(pinned, target)){
            bishop = bb::lsbReset(bishop);
            continue;
        }

        U64 options = bb::generateBishopAttack(target, occ);

        // captures and quiet moves respectively
        U64 captures = options & opp;
        U64 quietMoves = options & empty;

        // adds masks
        captures &= capMask;
        quietMoves &= moveMask;

        while(captures){
            to = bb::bitscanForward(captures);
            movelist.add(genMoveCap(target, to,CAPTURE, BISHOP, boardArr[to].first));

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
    // bitboard of current and opp color's bishop
    U64 bishop;
    U64 oppBishop;

    // all pieces of both sides
    U64 opp;
    U64 team;

    // this color's king
    U64 king;

    // current queen
    U64 queen;

    if (color == white){
        opp = bitBoard.bit_boards[black];
        team = bitBoard.bit_boards[white];
    }
    else{
        opp = bitBoard.bit_boards[white];
        team = bitBoard.bit_boards[black];
    }

    bishop = bitBoard.bit_boards[BISHOP] & team;
    oppBishop = bitBoard.bit_boards[BISHOP] & opp;
    queen = bitBoard.bit_boards[QUEEN] & team;


    // all occupied squares
    U64 occ = 0ULL;

    for (int i = 0; i < 8; i++){
        occ |= bitBoard.bit_boards[i];
    }

    U64 empty = ~occ;

    Square target;
    Square to;

    while (queen){
        target = bb::bitscanForward(queen);
        U64 options = bb::generateBishopAttack(target, occ) | bb::generateRookAttack(target, occ);

        // captures and quiet moves respectively
        U64 captures = options & opp;
        U64 quietMoves = options & empty;

        // adds masks
        captures &= capMask;
        quietMoves &= moveMask;

        while(captures){
            to = bb::bitscanForward(captures);
            movelist.add(genMoveCap(target, to,CAPTURE, QUEEN, boardArr[to].first));

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
    // bitboard of current and opp color's bishop
    U64 bishop;
    U64 oppBishop;

    // all pieces of both sides
    U64 opp;
    U64 team;

    // this color's king
    U64 king;

    U64 oppQueen;

    if (color == white){
        opp = bitBoard.bit_boards[black];
        team = bitBoard.bit_boards[white];
    }
    else{
        opp = bitBoard.bit_boards[white];
        team = bitBoard.bit_boards[black];
    }

    bishop = bitBoard.bit_boards[BISHOP] & team;
    oppBishop = bitBoard.bit_boards[BISHOP] & opp;
    king =  bitBoard.bit_boards[KING] & team;
    oppQueen = bitBoard.bit_boards[QUEEN] & opp;


    // all occupied squares
    U64 occ = 0ULL;

    for (int i = 0; i < 8; i++){
        occ |= bitBoard.bit_boards[i];
    }

    U64 empty = ~occ;

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

    // only legal moves
    oppCaptures = ~oppCaptures;

    king2 &= oppCaptures;

    // gets the captures and quiet moves
    U64 attacks = king2 & opp;
    U64 quiet = king2 & empty;

    // adds masks
    attacks &= capMask;
    quiet &= moveMask;


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



}

void moveGen::genHorse() {
    // bitboard of current and opp color's bishop
    U64 horse;
    U64 oppHorse;

    // all pieces of both sides
    U64 opp;
    U64 team;

    // this color's king
    U64 curKing;

    U64 oppQueen;

    if (color == white){
        opp = bitBoard.bit_boards[black];
        team = bitBoard.bit_boards[white];
    }
    else{
        opp = bitBoard.bit_boards[white];
        team = bitBoard.bit_boards[black];
    }

    horse = bitBoard.bit_boards[HORSE] & team;
    oppHorse = bitBoard.bit_boards[HORSE] & opp;
    curKing =  bitBoard.bit_boards[KING] & team;
    oppQueen = bitBoard.bit_boards[QUEEN] & opp;


    // all occupied squares
    U64 occ = 0ULL;

    for (int i = 0; i < 8; i++){
        occ |= bitBoard.bit_boards[i];
    }

    U64 empty = ~occ;

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
        U64 quietMoves = temp & empty;

        // adds masks
        captures &= capMask;
        quietMoves &= moveMask;

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
}

PieceTypes moveGen::getCapPiece(Square square) {
    return boardArr[square].first;
}
