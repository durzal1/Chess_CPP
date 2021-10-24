//
// Created by zacky on 10/21/2021.
//

#ifndef CHESS_MOVEGENERATOR_H
#define CHESS_MOVEGENERATOR_H
#include "board.h"
#include "moveList.h"
struct moveGen{
private:
    bitboard bitBoard;
    piece boardArr [64];
    moveList movelist;

    // bitboard of all the potential captures the enemy can do (helps with making moves legal)
    U64 oppCaptures = 0ULL;

    // bitboard that does all type moves from king (checks how many ways we're in check)
    U64 attackers = 0ULL;

    Color color;
public:
    moveGen();

    moveGen(const bitboard &bitBoard, Color color, piece arr[]);

    /**
     * generates all white pawn quiet moves and updates the moveList
     */
    void genPawnQuiet();

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

};



#endif //CHESS_MOVEGENERATOR_H
