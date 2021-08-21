//
// Created by zacky on 8/16/2021.
//

#include "ai.h"

ai::ai(board Board, int maxDepth) {
    // gets the max depth recursive function will go to (+1 is to make depth more accurate)
    this->maxDepth = maxDepth;

    /// HERE ADD A FOR LOOP TO GO THROUGH EVERY PIECE AND ITS MOVES FIRST

    int total = 0;
    for (int index:Board.whitePieces){

        int addTotal = 0;

        // class of piece
        std::string className = Board.IndClass[index - 1];

        // gets its row and column
        std::pair<int,int> newCords = Board.PieceLoc[index];

        int row = newCords.first;
        int col = newCords.second;

        std::vector<std::tuple<int, int, bool>> moves = posMoves(className, row, col, "white", Board.BoardLoc, Board.inter, Board.renderer);

        // the bool is not yet implemented, states whether the move will cause a capture
        for (auto move : moves) {
            int row_ = std::get<0>(move);
            int col_ =  std::get<1>(move);
            bool Captured = std::get<2>(move);
            getScores(Board, index, "black", 1, row_,col_, Captured, addTotal);
        }
        total += addTotal;
    }
    std::cout << total;

}

// @param Board, this is the Board class that contains all the information of the board
// @param index, index of the piece
// @param color, color of the peice (black or white)
// @param depth, current depth of the recursive search
// @param Row, this is the row that the piece is currently moving to that we need to update in the Board data classes
// @param Col, same as former except the column
// @param captured, checks if piece is captured by its move
// @param totalMoves, for debugging checks how many moves have occured
void ai::getScores(board Board, int index, std::string color, int depth, int Row, int Col, bool captured, int &totalMoves) {

	// get next color
	std::string nextColor;

	auto pieces = Board.whitePieces; // pieces store current color pieces being searched, white by default

	if (color == "black") {
		nextColor = "white";
		if (captured) { // black piece was captured on the last turn by white since it is black's turn now
		    // gets index of black piece
		    int ind = Board.BoardLoc[{Row, Col}];

		    // erases it
		    Board.whitePieces.erase(ind);

//			Board.blackPieces.erase(Board.blackPieces.begin() + Board.BoardLoc[{Row, Col}] - 2);
		}
		pieces = Board.blackPieces;
	}
	else {
		nextColor = "black";
		if (captured) { // white piece was captured on the last turn by black since it is white's turn now
		    // gets index of white piece and erases it
		    int ind = Board.BoardLoc[{Row, Col}] ;

		    // erases it
		    Board.whitePieces.erase(ind);
		}
	}

    // set the old cord to have no piece inside of it
    std::pair<int,int> oldCords = Board.PieceLoc[index];

	// deletes the key
	Board.BoardLoc.erase({oldCords.first, oldCords.second});

	// update the row and column in data classes
	Board.PieceLoc[index] = { Row, Col };
	Board.BoardLoc[{Row, Col}] = index;

	//// REMOVE THIS LATER IT IS FOR TESTING ONLY AND USES A LOT OF MEMORY
//	Board.createBoard();

	// puts the base case later so it can the piece can do the move before it ends returns
	if (depth == maxDepth) {
	    totalMoves ++;
	    return;
	}

	// if white it will check to see if any blacks next moves can kill the king (check)
	if (color == "white"){
	    for (int piece:Board.blackPieces){
	        std::string className = Board.IndClass[piece - 1];

	        // gets its row and column
	        std::pair<int,int> newCords = Board.PieceLoc[piece];

	        int row = newCords.first;
	        int col = newCords.second;

	        std::vector<std::tuple<int, int, bool>> moves = posMoves(className, row, col, color, Board.BoardLoc, Board.inter, Board.renderer);
	        // the bool is not yet implemented, states whether the move will cause a capture

	        for (auto move : moves) {
	            int row_ = std::get<0>(move);
	            int col_ =  std::get<1>(move);
	            bool Captured = std::get<2>(move);

	            // it captures a piece
	            if (Captured){
	                // get index of the piece it captures
	                int pieceInd = Board.BoardLoc[{row_, col_}];

	                // gets class
	                std::string Class = Board.IndClass[pieceInd-1];

	                // checks if its a king
	                if (Class == "king"){
	                    // it is now check
	                    check = true;
	                }
	            }

	        }
	    }
	}
	// if it is check
	if (check){
	    // iterate through each piece
	    for (int piece : pieces){
	        std::string className = Board.IndClass[piece - 1];

	        // gets its row and column
	        std::pair<int,int> newCords = Board.PieceLoc[piece];

	        int row = newCords.first;
	        int col = newCords.second;

	        std::vector<std::tuple<int, int, bool>> moves = posMoves(className, row, col, color, Board.BoardLoc, Board.inter, Board.renderer);

	        //
	        for (auto move : moves) {
	            int row_ = std::get<0>(move);
	            int col_ =  std::get<1>(move);
	            bool Captured = std::get<2>(move);
	            getScores(Board, piece, nextColor, depth+1, row_,col_, Captured, totalMoves);

	        }
	    }
	}
	// not check so proceed normally
	else{
	    // class of piece
	    for (auto piece : pieces) {
	        std::string className = Board.IndClass[piece - 1];

	        // gets its row and column
	        std::pair<int,int> newCords = Board.PieceLoc[piece];

	        int row = newCords.first;
	        int col = newCords.second;

	        std::vector<std::tuple<int, int, bool>> moves = posMoves(className, row, col, color, Board.BoardLoc, Board.inter, Board.renderer);

	        // iterate through all of the moves
	        for (auto move : moves) {
	            int row_ = std::get<0>(move);
	            int col_ =  std::get<1>(move);
	            bool Captured = std::get<2>(move);
	            getScores(Board, piece, nextColor, depth+1, row_,col_, Captured, totalMoves);

	        }
	    }
	}

}

bool ai::moveCheck(board Board, int index, int row, int col) {

    return false;
}


// all the moves it will recursively call


// iterate through every possible move


