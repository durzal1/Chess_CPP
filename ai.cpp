//
// Created by zacky on 8/16/2021.
//

#include "ai.h"

ai::ai(board Board) {

	this->getScores(Board, 4, "black", 2, 4, 5, false);
	
}
// @param Board, this is the Board class that contains all the information of the board
// @param index, index of the piece
// @param color, color of the peice (black or white)
// @param depth, current depth of the recursive search
// @param Row, this is the row that the piece is currently moving to that we need to update in the Board data classes
// @param Col, same as former except the column
// @param captured, checks if piece is captured by its move
void ai::getScores(board Board, int index, std::string color, int depth, int Row, int Col, bool captured) {
	if (depth == 0) {
		return;
	}
		

	// get next color
	std::string nextColor;

	auto pieces = Board.whitePieces; // pieces store current color pieces being searched, white by default

	if (color == "black") {
		nextColor = "white";
		if (captured) { // black piece was captured on the last turn by white since it is black's turn now
			Board.blackPieces.erase(Board.blackPieces.begin() + Board.BoardLoc[{Row, Col}] - 1); // gets index of black piece and erases it
			// MAY NOT BE CORRECT INDEX WITH THE -1
		}
		pieces = Board.blackPieces;
	}
	else {
		nextColor = "black";
		if (captured) { // white piece was captured on the last turn by black since it is white's turn now
			Board.whitePieces.erase(Board.whitePieces.begin() + Board.BoardLoc[{Row, Col}] - 1); // gets index of white piece and erases it
			// MAY NOT BE CORRECT INDEX WITH THE -1
		}
	}


	// update the row and column in data classes
	Board.PieceLoc[index] = { Row, Col };
	Board.BoardLoc[{Row, Col}] = index;



	// class of piece

	for (auto piece : pieces) {
		std::string className = Board.IndClass[piece - 1];

		std::vector<std::tuple<int, int, bool>> moves = posMoves(className, Row, Col, color, Board.BoardLoc, Board.inter, Board.renderer);
		// the bool is not yet implemented, states whether the move will cause a capture
		
		for (auto move : moves) {

			getScores(Board, piece, nextColor, depth - 1, std::get<0>(move), std::get<1>(move), std::get<2>(move));
			
		}
	}
}
// all the moves it will recursively call


// iterate through every possible move


