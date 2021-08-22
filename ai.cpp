//
// Created by zacky on 8/16/2021.
//

#include "ai.h"

ai::ai(board Board, int maxDepth) {
	// gets the max depth recursive function will go to (+1 is to make depth more accurate)
	this->maxDepth = maxDepth;

	/// HERE ADD A FOR LOOP TO GO THROUGH EVERY PIECE AND ITS MOVES FIRST

	int total = 0;
	for (int index : Board.whitePieces) {

		int addTotal = 0;

		// class of piece
		std::string className = Board.IndClass[index - 1];

		// gets its row and column
		std::pair<int, int> newCords = Board.PieceLoc[index];

		int row = newCords.first;
		int col = newCords.second;

		std::vector<std::tuple<int, int, bool>> moves = posMoves(className, row, col, "white", Board); // , Board.renderer

		// the bool is not yet implemented, states whether the move will cause a capture
		for (auto move : moves) {
			int row_ = std::get<0>(move);
			int col_ = std::get<1>(move);
			bool Captured = std::get<2>(move);

			getScores(Board, index, "black", 1, row_, col_, Captured, addTotal);
		}
		total += addTotal;
	}
	std::cout << total;

}

void ai::getScores(board Board, int index, std::string color, int depth, int Row, int Col, bool captured, int& totalMoves) {

	// get next color
	std::string nextColor;

	auto pieces = Board.whitePieces; // pieces store current color pieces being searched, white by default
	auto opposingPieces = Board.blackPieces;
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
		opposingPieces = Board.whitePieces;
	}
	else {
		nextColor = "black";
		if (captured) { // white piece was captured on the last turn by black since it is white's turn now
			// gets index of white piece and erases it
			int ind = Board.BoardLoc[{Row, Col}];

			// erases it
			Board.whitePieces.erase(ind);
		}
	}

    // not a castle move

    // set the old cord to have no piece inside of it
    std::pair<int, int> oldCords = Board.PieceLoc[index];

	// deletes the key
	Board.BoardLoc.erase({ oldCords.first, oldCords.second });

	// update the row and column in data classes
	Board.PieceLoc[index] = { Row, Col };
	Board.BoardLoc[{Row, Col}] = index;



	//// REMOVE THIS LATER IT IS FOR TESTING ONLY AND USES A LOT OF MEMORY
//	Board.createBoard();

	// puts the base case later so it can the piece can do the move before it ends returns
	if (depth == maxDepth) {
		totalMoves++;
		return;
	}
//
//	// if its a king that moved or one of rooks then player or ai lost their right to castle
//	if (Board.IndClass[index-1] == "king"){
//	    if (color == "white"){
//	        Board.whiteCastleRight = false;
//	        Board.whiteCastleLeft = false;
//	    }else{
//	        Board.blackCastleRight = false;
//	        Board.blackCastleLeft = false;
//	    }
//	}
//	else if (Board.IndClass[index-1] == "rook"){
//	    if (color == "white"){
//	        // check which side it is on
//            if (index == 17) Board.whiteCastleLeft = false;
//	        else if (index == 24) Board.whiteCastleRight = false;
//	    }else{
//	        if (index == 1) Board.blackCastleLeft = false;
//            else if (index == 7)Board.blackCastleRight = false;
//	    }
//	}
	/// if there is check i am not going to look to see if castle can help it

	// index of king
    int kingInd;
    if (color == "black") kingInd = 5;
    else kingInd = 21;


    // gets its row and column
    std::pair<int, int> newCords = Board.PieceLoc[kingInd];
    int row = newCords.first;
    int col = newCords.second;

    // check all of opposite color's moves in case of check
    // moves correlates to the amount of pieces that can kill the king
//    int moves = kingAttacks(Board, color, row, col);

	// here any move can help get out of check
//	if (moves == 1) {
//	    bool checkMate = true;
//		// iterate through each piece
//		for (int piece : pieces) {
//			std::string className = Board.IndClass[piece - 1];
//
//			// gets its row and column
//			std::pair<int, int> NewCords = Board.PieceLoc[piece];
//
//			int Row_ = NewCords.first;
//			int Col_ = NewCords.second;
//
//			std::vector<std::tuple<int, int, bool, std::string>> Moves = posMoves(className, Row_, Col_, color, Board); // Board.renderer
//
//
//			for (auto move : Moves) {
//
//				int row_ = std::get<0>(move);
//				int col_ = std::get<1>(move);
//				bool Captured = std::get<2>(move);
//				std::string Castle = std::get<3>(move);
//
//				// castle is possible but again i don't want to deal with this for now
//				if (!Castle.empty()) continue;
//
//				if (!moveCheck(Board, color, piece, row_, col_, Captured)) { // if not in check after move (valid)
//					checkMate = false;
//					getScores(Board, piece, nextColor, depth + 1, row_, col_, Captured, totalMoves, "");
//				}
//			}
//		}
//		if (checkMate){
//		    // add one to moves and return since the game is over
//		    totalMoves++;
//		    return;
//		}
//	}
//
//	// here only the king is allowed to move
//	else if (moves == 2){
//	    std::string className = Board.IndClass[kingInd - 1];
//
//	    // gets its row and column
//	    std::pair<int, int> newCords = Board.PieceLoc[kingInd];
//
//	    int row = newCords.first;
//	    int col = newCords.second;
//
//	    std::vector<std::tuple<int, int, bool, std::string>> moves = posMoves(className, row, col, color, Board);
//
//	    bool checkMate = true;
//	    for (auto move:moves){
//	        int row_ = std::get<0>(move);
//	        int col_ = std::get<1>(move);
//	        bool Captured = std::get<2>(move);
//	        std::string Castle = std::get<3>(move);
//
//	        // castle is possible but again i don't want to deal with this for now
//            if (!Castle.empty()) continue;
//
//	        if (!moveCheck(Board, color, kingInd, row_, col_, Captured)) { // if not in check after move (valid)
//	            checkMate = false;
//	            getScores(Board, kingInd, nextColor, depth + 1, row_, col_, Captured, totalMoves, "");
//	        }
//	    }
//	    if (checkMate){
//	        // add one to moves and return since the game is over
//	        totalMoves++;
//	        return;
//	    }
//	}
	// no check to worry about
	if (true) {

		// class of piece
		for (auto piece : pieces) {
			std::string className = Board.IndClass[piece - 1];

			// gets its row and column
			std::pair<int, int> NewCords = Board.PieceLoc[piece];

			int row1 = NewCords.first;
			int col1 = NewCords.second;

			std::vector<std::tuple<int, int, bool>> Moves = posMoves(className, row1, col1, color, Board); // , Board.renderer

			// iterate through all of the moves
			for (auto move : Moves) {
				int row_ = std::get<0>(move);
				int col_ = std::get<1>(move);
				bool Captured = std::get<2>(move);
//				std::string Castle = std::get<3>(move);

				getScores(Board, piece, nextColor, depth + 1, row_, col_, Captured, totalMoves);

			}
		}
	}

}

bool ai::moveCheck(board Board, std::string color, int index, int row, int col, bool captured) {

	auto opposingPieces = Board.whitePieces;
	if (color == "black") {

		if (captured) { // black piece was captured on the last turn by white since it is black's turn now
			// gets index of black piece
			int ind = Board.BoardLoc[{row, col}];

			// erases it
			Board.whitePieces.erase(ind);

			//			Board.blackPieces.erase(Board.blackPieces.begin() + Board.BoardLoc[{Row, Col}] - 2);
		}
		opposingPieces = Board.blackPieces;
	}
	else {

		if (captured) { // white piece was captured on the last turn by black since it is white's turn now
			// gets index of white piece and erases it
			int ind = Board.BoardLoc[{row, col}];

			// erases it
			Board.whitePieces.erase(ind);
		}
	}

	// set the old cord to have no piece inside of it
	std::pair<int, int> oldCords = Board.PieceLoc[index];

	// deletes the key
	Board.BoardLoc.erase({ oldCords.first, oldCords.second });

	// update the row and column in data classes
	Board.PieceLoc[index] = { row, col };
	Board.BoardLoc[{row, col}] = index;

	// index of king
	int kingInd;
	if (color == "black") kingInd = 5;
	else kingInd = 21;


	// gets its row and column
	std::pair<int, int> newCords = Board.PieceLoc[kingInd];
	row = newCords.first;
	col = newCords.second;

	int moves = kingAttacks(Board, color, row, col);

	if (moves == 0) return false;
	else return true;
}

int ai::kingAttacks(board Board, std::string color, int row, int col) {
    auto BoardLoc = Board.BoardLoc;

    // moves that can attack the king
    int killingMoves = 0;

    // look at the possible pawn moves
    if (color == "white"){
        // here we check the black pawn attacks

        // get the row and col for the attacks
        int newRow = row-1;
        int newCol = row+1;

        if (Board.BoardLoc.find({ newRow ,newCol }) != Board.BoardLoc.end()) {
            // there is a piece there, so now we check if it's the enemies

            // get the index of the piece
            int index = Board.BoardLoc[{newRow ,newCol}];

            // class of piece
            std::string Class = Board.IndClass[index-1];

            // checks if its black
            if (index <= 16 && Class == "pawn" ) {
                // legal move
                // true since there is an enemy pawn
                killingMoves ++;
            }
        }

        newRow = row-1;
        newCol = row-1;

        if (Board.BoardLoc.find({ newRow ,newCol }) != Board.BoardLoc.end()) {
            // there is a piece there, so now we check if it's the enemies

            // get the index of the piece
            int index = Board.BoardLoc[{newRow ,newCol}];

            // class of piece
            std::string Class = Board.IndClass[index-1];

            // checks if its black
            if (index <= 16 && Class == "pawn" ) {
                // legal move
                // true since there is an enemy pawn
                killingMoves ++;
            }
        }
    }
    else{
        // get the row and col for the attacks
        int newRow = row+1;
        int newCol = row+1;

        if (Board.BoardLoc.find({ newRow ,newCol }) != Board.BoardLoc.end()) {
            // there is a piece there, so now we check if it's the enemies

            // get the index of the piece
            int index = Board.BoardLoc[{newRow ,newCol}];

            // class of piece
            std::string Class = Board.IndClass[index-1];

            // checks if its black
            if (index > 16 && Class == "pawn" ) {
                // legal move
                // true since there is an enemy pawn
                killingMoves ++;
            }
        }

        newRow = row+1;
        newCol = row-1;

        if (Board.BoardLoc.find({ newRow ,newCol }) != Board.BoardLoc.end()) {
            // there is a piece there, so now we check if it's the enemies

            // get the index of the piece
            int index = Board.BoardLoc[{newRow ,newCol}];

            // class of piece
            std::string Class = Board.IndClass[index-1];

            // checks if its black
            if (index > 16 && Class == "pawn" ) {
                // legal move
                // true since there is an enemy pawn
                killingMoves ++;
            }
        }
    }
    /// horse moves
    // vector of all possible moves here (could be illegal)
    std::vector<std::pair<int, int>> moves;

    // variables needed
    int col_down1 = col + 1;
    int col_down2 = col + 2;
    int col_up1 = col - 1;
    int col_up2 = col - 2;

    int row_right1 = row + 1;
    int row_right2 = row + 2;
    int row_left1 = row - 1;
    int row_left2 = row - 2;

    // adds all the moves
    moves.emplace_back(row_right1, col_down2);
    moves.emplace_back(row_left1, col_down2);

    moves.emplace_back(row_left2, col_down1);
    moves.emplace_back(row_left2, col_up1);

    moves.emplace_back(row_left1, col_up2);
    moves.emplace_back(row_right1, col_up2);

    moves.emplace_back(row_right2, col_up1);
    moves.emplace_back(row_right2, col_down1);

    int newRow;
    int newCol;
    for (std::pair<int, int> pair : moves) {
        newRow = pair.first;
        newCol = pair.second;

        // makes sure its in bounds
        if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) continue;

        if (BoardLoc.find({ newRow,newCol }) != BoardLoc.end()) {
            // check if it's the enemy's piece
            // get the index
            int index = BoardLoc[{newRow, newCol}];

            // gets the class
            std::string Class = Board.IndClass[index - 1];

            // color
            std::string Color;

            if (index > 16) Color = "white";
            else Color = "black";

            if (color != Color && Class == "horse") {
                killingMoves++;
                if (killingMoves >= 2) return 2;
            }
        }
    }

    /// king moves
    moves.clear();

    // adds all possible moves
    int new_col_up = col - 1;
    int new_col_down = col + 1;

    int new_row_left = row - 1;
    int new_row_right = row + 1;

    moves.emplace_back(row, new_col_up);
    moves.emplace_back(row, new_col_down);

    moves.emplace_back(new_row_right, col);
    moves.emplace_back(new_row_left, col);

    moves.emplace_back(new_row_right, new_col_down);
    moves.emplace_back(new_row_right, new_col_up);

    moves.emplace_back(new_row_left, new_col_down);
    moves.emplace_back(new_row_left, new_col_up);

    for (std::pair<int, int> pair : moves) {
        newRow = pair.first;
        newCol = pair.second;

        // makes sure its in bounds
        if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) continue;

        // checks if the move is legal

        if (BoardLoc.find({ newRow,newCol }) != BoardLoc.end()) {
            // check if it's the enemy's piece

            // get the index
            int index = BoardLoc[{newRow, newCol}];

            // gets the class
            std::string Class = Board.IndClass[index - 1];

            // color
            std::string Color;

            if (index > 16) Color = "white";
            else Color = "black";

            if (color != Color && Class == "king") {
                killingMoves++;
                if (killingMoves >= 2) return 2;
            }
        }
    }

    /// queen
    // boolean variables to determine whether we should continue going a specific direction
    // this is useful because if it is going up and sees an obstacle it can not go up further
    // so this is the indicator to not go up anymore
    bool goUp = true;
    bool goDown = true;
    bool goRight = true;
    bool goLeft = true;
    bool goTopLeft = true;
    bool goBtmRight = true;
    bool goTopRight = true;
    bool goBtmLeft = true;

    for (int i = 1; i <= 8; i++) {

        // up
        newRow = row - i;
        newCol = col;

        // add to moves vector
        moves.emplace_back(newRow, newCol);

        // down
        newRow = row + i;
        newCol = col;

        moves.emplace_back(newRow, newCol);

        // right
        newRow = row;
        newCol = col + i;

        moves.emplace_back(newRow, newCol);

        // left
        newRow = row;
        newCol = col - i;

        moves.emplace_back(newRow, newCol);

        // up left
        newRow = row - i;
        newCol = col - i;


        // add to moves vector
        moves.emplace_back(newRow, newCol);

        // down right
        newRow = row + i;
        newCol = col + i;

        moves.emplace_back(newRow, newCol);

        // down right
        newRow = row - i;
        newCol = col + i;

        moves.emplace_back(newRow, newCol);

        // down left
        newRow = row + i;
        newCol = col - i;

        moves.emplace_back(newRow, newCol);
    }
    // iterate through the possible moves to find which ones are legal
    for (int i = 0; i < moves.size(); i++) {
        std::pair<int, int> pair = moves[i];
        newRow = pair.first;
        newCol = pair.second;

        // makes sure its in bounds
        if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) continue;

        // determine which direction it is going
        // we do this by looking at the remainder (1 = up, 2 = down, 3 = right, 4 = left, 5 topRight...)
        Direction dir = Direction((i + 8) % 8);

        // check to see if we can keep going that direction
        if (dir == Up && !goUp || dir == Down && !goDown || dir == Right && !goRight || dir == Left && !goLeft || dir == topLeft && !goTopLeft || dir == topRight && !goTopRight ||
        dir == bottomLeft && !goBtmLeft || dir == bottomRight && !goBtmRight) continue;

        // check if the move is legal
        bool legal = true;

        // if there is a piece on the square
        if (BoardLoc.find({ newRow,newCol })!= BoardLoc.end()) {
            // make sure its the enemies

            // get the index
            int index = BoardLoc[{newRow, newCol}];

            // gets the class
            std::string Class = Board.IndClass[index - 1];

            // color
            std::string Color;

            if (index > 16) Color = "white";
            else Color = "black";

            if (color != Color && Class == "queen") {
                killingMoves++;
                if (killingMoves >= 2) return 2;
            }
            legal = false;
        }
        if (!legal) {
            // we make it illegal to go that direction
            if (dir == Up) goUp = false;
            else if (dir == Down) goDown = false;
            else if (dir == Right) goRight = false;
            else if (dir == Left) goLeft = false;
            else if (dir == topLeft) goTopLeft = false;
            else if (dir == topRight) goTopRight = false;
            else if (dir == bottomLeft) goBtmLeft = false;
            else if (dir == bottomRight) goBtmRight = false;
        }
    }


    /// rook moves
    // this is useful because if it is going up and sees an obstacle it can not go up further
    // so this is the indicator to not go up anymore
    goUp = true;
    goDown = true;
    goRight = true;
    goLeft = true;

    moves.clear();
    for (int i = 1; i <= 8; i++) {

        // up
        newRow = row - i;
        newCol = col;

        // add to moves vector
        moves.emplace_back(newRow, newCol);

        // down
        newRow = row + i;
        newCol = col;

        moves.emplace_back(newRow, newCol);

        // right
        newRow = row;
        newCol = col + i;

        moves.emplace_back(newRow, newCol);

        // left
        newRow = row;
        newCol = col - i;

        moves.emplace_back(newRow, newCol);
    }
    // iterate through the possible moves to find which ones are legal
    for (int i = 0; i < moves.size(); i++) {
        std::pair<int, int> pair = moves[i];
        newRow = pair.first;
        newCol = pair.second;

        // makes sure its in bounds
        if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) continue;

        // determine which direction it is going
        // we do this by looking at the remainder (1 = up, 2 = down, 3 = right, 4 = left)
        Direction dir = Direction((i + 4) % 4);

        // check to see if we can keep going that direction
        if (dir == Up && !goUp || dir == Down && !goDown || dir == Right && !goRight || dir == Left && !goLeft) continue;

        // check if the move is legal
        bool legal = true;

        // if there is a piece on the square
        if (BoardLoc.find({ newRow,newCol }) != BoardLoc.end()) {
            // make sure its the enemies

            // get the index
            int index = BoardLoc[{newRow, newCol}];

            // gets the class
            std::string Class = Board.IndClass[index - 1];

            // color
            std::string Color;

            if (index > 16) Color = "white";
            else Color = "black";

            if (color != Color && Class == "rook") {
                killingMoves++;
                if (killingMoves >= 2) return 2;
            }
            legal = false;
        }
        if (!legal) {
            // we make it illegal to go that direction
            if (dir == Up) goUp = false;
            else if (dir == Down) goDown = false;
            else if (dir == Right) goRight = false;
            else if (dir == Left) goLeft = false;
        }
    }
    /// bishop
    // boolean variables to determine whether we should continue going a specific direction
    // this is useful because if it is going up and sees an obstacle it can not go up further
    // so this is the indicator to not go up anymore
    goUp = true;
    goDown = true;
    goRight = true;
    goLeft = true;

    moves.clear();
    for (int i = 1; i <= 8; i++) {

        // up left
        newRow = row - i;
        newCol = col - i;

        // add to moves vector
        moves.emplace_back(newRow, newCol);

        // down right
        newRow = row + i;
        newCol = col + i;

        moves.emplace_back(newRow, newCol);

        // down right
        newRow = row - i;
        newCol = col + i;

        moves.emplace_back(newRow, newCol);

        // down left
        newRow = row + i;
        newCol = col - i;

        moves.emplace_back(newRow, newCol);

    }

    // iterate through the possible moves to find which ones are legal
    for (int i = 0; i < moves.size(); i++) {
        std::pair<int, int> pair = moves[i];
        newRow = pair.first;
        newCol = pair.second;

        // determine which direction it is going
        // we do this by looking at the remainder (1 = up, 2 = down, 3 = right, 4 = left)
        Direction dir = Direction((i + 4) % 4);

        // makes sure its in bounds
        if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) continue;

        // check to see if we can keep going that direction
        if (dir == Up && !goUp || dir == Down && !goDown || dir == Right && !goRight || dir == Left && !goLeft) continue;

        // check if the move is legal
        bool legal = true;

        // if there is a piece on the square
        if (BoardLoc.find({ newRow,newCol }) != BoardLoc.end()) {
            // make sure its the enemies

            // get the index
            int index = BoardLoc[{newRow, newCol}];

            // gets the class
            std::string Class = Board.IndClass[index - 1];

            // color
            std::string Color;

            if (index > 16) Color = "white";
            else Color = "black";

            if (color != Color && Class == "bishop") {
                killingMoves++;
                if (killingMoves >= 2) return 2;
            }
            legal = false;
        }
        if (!legal) {
            // we make it illegal to go that direction
            if (dir == Up) goUp = false;
            else if (dir == Down) goDown = false;
            else if (dir == Right) goRight = false;
            else if (dir == Left) goLeft = false;
        }
    }
    return killingMoves;
}




// all the moves it will recursively call


// iterate through every possible move


