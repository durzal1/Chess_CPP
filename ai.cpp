//
// Created by zacky on 8/16/2021.
//

#include "ai.h"
ai::ai(board Board) {

    this->getScores(Board,4, "black", 1, 4,5);

}
// @param Board, this is the Board class that contains all the information of the board
// @param index, index of the piece
// @param color, color of the peice (black or white)
// @param depth, current depth of the recursive search
// @param Row, this is the row that the piece is currently moving to that we need to update in the Board data classes
// @param Col, same as former except the column
void ai::getScores(board Board, int index, std::string color, int depth, int Row, int Col) {
    // update the row and column in data classes
    Board.PieceLoc[index] = {Row, Col};
    Board.BoardLoc[{Row,Col}] = index;

    // get next color
    std::string nextColor;

    if (color == "black") nextColor = "white";
    else nextColor = "black";

    // class of piece
    std::string className = Board.IndClass[index - 1];

    // all the moves it will recursively call
    std::vector<std::pair<int, int>> moves = posMoves(className, Row, Col, color, Board.BoardLoc, Board.inter, Board.renderer);


    // iterate through every possible move
    for (std::pair<int,int> move:moves){
        getScores(Board, index, nextColor, depth +1, move.first, move.second);
    }
}

