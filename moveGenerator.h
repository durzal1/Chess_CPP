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
    piece boardArr [64];
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

    moveGen(const bitboard &bitBoard, Color color, piece arr[]);

    /**
     * generates all pawn quiet moves and updates the moveList
     */
    void genPawnQuiet();


    /**
     * generates pawn Cap moves for a specific bitboard (for when pawn is pinned)
     */
    void pinPawnCap(int piece, int pinningPiece);

    /**
    * generates all white pawn capture moves and updates the moveList
    */
    void genPawnCap();

    /**
   * generates all rook moves and updates the moveList
   */
    void genRook();

    /**
  * generates all bishop moves and updates the moveList
  */
    void genBishop();

    /**
  * generates all Queen moves and updates the moveList
  */
    void genQueen();

    /**
 * generates all king moves and updates the moveList
 */
    void genKing();

    /**
* generates all horse moves and updates the moveList
*/
    void genHorse();

    /**
     * generates the moves for all pinned pieces
     */
     void getPinnedMoves();

    /**
     * given the square index, returns the piece that is captured
     * @return square
     * @return captured piece
     */
    PieceTypes getCapPiece(Square square);

    /**
     * generates all the possible psuedo-legal moves and only returns legal moves
     * @return moveList
     */
    moveList genAll();

    /**
     * generates the attackers bitboard and thus the amount of checks
     * pretty disorganized since i pile everthing in here
     * i would put everything in its respective gen but it would make program slower
     */
    void genChecks();

};



#endif //CHESS_MOVEGENERATOR_H
