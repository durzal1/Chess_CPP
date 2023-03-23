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


