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
    moveList movelist;

    Color color;
public:
    moveGen();

    moveGen(const bitboard &bitBoard, Color color);

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

    void genAll();

};



#endif //CHESS_MOVEGENERATOR_H
