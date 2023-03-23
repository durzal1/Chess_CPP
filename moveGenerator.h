//
// Created by zacky on 10/21/2021.
//

#ifndef CHESS_MOVEGENERATOR_H
#define CHESS_MOVEGENERATOR_H
#include "board.h"
#include "moveList.h"
#include <bitset>
#include <cstdint>
#include <initializer_list>
#include <iostream>
struct moveGen{
private:
    bitboard bitBoard;
    std::pair<PieceTypes, Color> boardArr [64];
    moveList movelist;

    // bitboard of all the potential captures the enemy can do (determines king legal moves)
    U64 oppCaptures = 0ULL;

    // bitboard that does all type moves from king (checks how many ways we're in check)
    U64 attackers = 0ULL;

    // mask of all the square that can be captured (limited to one during check)
    U64 capMask = ~0ULL;

    // mask of all the square that can be moved to (limited to path between attacking piece and king during check)
    U64 moveMask = ~0ULL;

    // bitboard of sliding moves from our king
    U64 kingSliding = 0ULL;

    // bitboard of opponent's sliding moves
    U64 oppSliding = 0ULL;

    // bitboard of all the pinned pieces
    U64 pinned = 0ULL;

    Color color;
public:
    moveGen();

    moveGen(const bitboard &bitBoard, Color color,  std::pair<PieceTypes, Color> arr[]);

    /**
     * generates all pawn quiet moves and updates the moveList
     */
    inline void genPawnQuiet();


    /**
     * generates pawn Cap moves for a specific bitboard (for when pawn is pinned)
     */
     inline void pinPawnCap(int piece, int pinningPiece);

    /**
    * generates all white pawn capture moves and updates the moveList
    */
    inline  void genPawnCap();

    /**
   * generates all rook moves and updates the moveList
   */
    inline void genRook();

    /**
  * generates all bishop moves and updates the moveList
  */
    inline void genBishop();

    /**
  * generates all Queen moves and updates the moveList
  */
     inline void genQueen();

    /**
 * generates all king moves and updates the moveList
 */
    inline void genKing();

    /**
* generates all horse moves and updates the moveList
*/
     inline void genHorse();

    /**
     * generates the moves for all pinned pieces
     */
     inline void getPinnedMoves();

    /**
     * given the square index, returns the piece that is captured
     * @return square
     * @return captured piece
     */
     inline PieceTypes getCapPiece(Square square);

    /**
     * generates all the possible psuedo-legal moves and only returns legal moves
     * @return moveList
     */
    inline moveList& genAll();

    /**
     * generates the attackers bitboard and thus the amount of checks
     * pretty disorganized since i pile everthing in here
     * i would put everything in its respective gen but it would make program slower
     */
    inline void genChecks();

};

inline moveList &moveGen::genAll(){
//        // gets number of ways check is made
//        genChecks();
//
//        // moves for pinned pieces
//        getPinnedMoves();
//
//        // always needed
//        genKing();

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

    return this->movelist;
}

inline PieceTypes moveGen::getCapPiece(Square square) {
    return boardArr[square].first;
}
inline void moveGen::genHorse() {
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
inline void moveGen::pinPawnCap(int piece, int pinningPiece) {
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

inline void moveGen::genPawnQuiet() {

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
inline void moveGen::genPawnCap() {


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

inline void moveGen::genRook(){


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

inline void moveGen::genBishop(){
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

inline void moveGen::genQueen(){
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

inline void moveGen::genKing(){
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



#endif //CHESS_MOVEGENERATOR_H
