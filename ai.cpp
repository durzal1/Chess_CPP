//
// Created by zacky on 8/16/2021.
//

#include "ai.h"

ai::ai(const board& b, int maxDepth, Color color) {
	// gets the max depth recursive function will go to (+1 is to make depth more accurate)
	this->maxDepth = maxDepth;

//    for (auto move:moves){
//        i++;
//        if (i != 2) continue;
//        b.move(move);
//        auto c = perft(b, maxDepth, true, black);
//        std::cout << "==========================================" << c << std::endl;
//    }
	auto c = perft(b, maxDepth, true, color);
    std::cout << c;

}


//void ai::getScores(board Board, int index, std::string color, int depth, int Row, int Col, bool captured, int& totalMoves, std::string castle) {
//
//	// get next color
//	std::string nextColor;
//
//	auto pieces = Board.whitePieces; // pieces store current color pieces being searched, white by default
//	auto opposingPieces = Board.blackPieces;
//	if (color == "black") {
//		nextColor = "white";
//		if (captured) { // black piece was captured on the last turn by white since it is black's turn now
//			// gets index of black piece
//			int ind = Board.BoardLoc[{Row, Col}];
//
//			if (Row == 7 && Col == 0) { // if captures a rook, cant castle on that side
//				Board.whiteCastleLeft = false;
//			}
//			else if (Row == 7 && Col == 7) Board.whiteCastleRight = false;
//
//			// erases it
//			Board.whitePieces.erase(ind);
//
//			//			Board.blackPieces.erase(Board.blackPieces.begin() + Board.BoardLoc[{Row, Col}] - 2);
//		}
//		pieces = Board.blackPieces;
//		opposingPieces = Board.whitePieces;
//	}
//	else {
//		nextColor = "black";
//		if (captured) { // white piece was captured on the last turn by black since it is white's turn now
//			// gets index of white piece and erases it
//			int ind = Board.BoardLoc[{Row, Col}];
//
//			if (Row == 0 && Col == 0) { // if captures a rook, cant castle on that side
//				Board.blackCastleLeft = false;
//			}
//			else if (Row == 0 && Col == 7) Board.blackCastleRight = false;
//
//			// erases it
//			Board.whitePieces.erase(ind);
//		}
//	}
//	// checks if the move is a castle
//	if (!castle.empty()) {
//
//		// checks where the castle is located
//		if (castle == "whiteLeft") {
//			// deletes the old positions of king and rook
//			Board.BoardLoc.erase({ 7, 4 });
//			Board.BoardLoc.erase({ 7, 0 });
//
//			// update the row and column in data classes
//			Board.PieceLoc[17] = { 7, 3 };
//			Board.BoardLoc[{7, 3}] = 17;
//
//			Board.PieceLoc[21] = { 7, 2 };
//			Board.BoardLoc[{7, 2}] = 21;
//
//		}
//		else if (castle == "whiteRight") {
//			// deletes the old positions of king and rook
//			Board.BoardLoc.erase({ 7, 4 });
//			Board.BoardLoc.erase({ 7, 7 });
//
//			// update the row and column in data classes
//			Board.PieceLoc[24] = { 7, 5 };
//			Board.BoardLoc[{7, 5}] = 24;
//
//			Board.PieceLoc[21] = { 7, 6 };
//			Board.BoardLoc[{7, 6}] = 21;
//		}
//		else if (castle == "blackLeft") {
//			// deletes the old positions of king and rook
//			Board.BoardLoc.erase(std::pair<int, int>{ 0, 0 });
//			Board.BoardLoc.erase({ 0, 4 });
//
//			// update the row and column in data classes
//			Board.PieceLoc[1] = { 0, 3 };
//			Board.BoardLoc[{0, 3}] = 1;
//
//			Board.PieceLoc[5] = { 0, 2 };
//			Board.BoardLoc[{0, 2}] = 5;
//		}
//		else if (castle == "blackRight") {
//			// deletes the old positions of king and rook
//			Board.BoardLoc.erase({ 0, 7 });
//			Board.BoardLoc.erase({ 0, 4 });
//
//			// update the row and column in data classes
//			Board.PieceLoc[7] = { 0, 5 };
//			Board.BoardLoc[{0, 5}] = 7;
//
//			Board.PieceLoc[5] = { 0, 6 };
//			Board.BoardLoc[{0, 6}] = 5;
//		}
//		else {
//			std::cout << "broken fix castle";
//		}
//		std::cout << "F";
//	}
//	// not a castle move
//	else {
//		// set the old cord to have no piece inside of it
//		std::pair<int, int> oldCords = Board.PieceLoc[index];
//
//		// deletes the key
//		Board.BoardLoc.erase({ oldCords.first, oldCords.second });
//
//		// update the row and column in data classes
//		Board.PieceLoc[index] = { Row, Col };
//		Board.BoardLoc[{Row, Col}] = index;
//	}
//
//
//	//// REMOVE THIS LATER IT IS FOR TESTING ONLY AND USES A LOT OF MEMORY
//	//	Board.createBoard();
//
//	// puts the base case later so it can the piece can do the move before it ends returns
//	if (depth == 0) {
//		totalMoves++;
//		return;
//	}
//
//	// if its a king that moved or one of rooks then player or ai lost their right to castle
//	if (Board.IndClass[index - 1] == "king") {
//		if (color == "white") {
//			Board.whiteCastleRight = false;
//			Board.whiteCastleLeft = false;
//		}
//		else {
//			Board.blackCastleRight = false;
//			Board.blackCastleLeft = false;
//		}
//	}
//	else if (Board.IndClass[index - 1] == "rook") {
//		if (color == "white") {
//			// check which side it is on
//			if (index == 17) Board.whiteCastleLeft = false;
//			else if (index == 24) Board.whiteCastleRight = false;
//		}
//		else {
//			if (index == 1) Board.blackCastleLeft = false;
//			else if (index == 7)Board.blackCastleRight = false;
//		}
//	}
//	/// if there is check i am not going to look to see if castle can help it
//
//	// index of king
//	int kingInd;
//	if (color == "black") kingInd = 5;
//	else kingInd = 21;
//
//
//	// gets its row and column
//	std::pair<int, int> newCords = Board.PieceLoc[kingInd];
//	int row = newCords.first;
//	int col = newCords.second;
//
//	// check all of opposite color's moves in case of check
//	// moves correlates to the amount of pieces that can kill the king
//	int moves = kingAttacks(Board, color, row, col);
//
//	//     here any move can help get out of check
//	if (moves == 1) {
//		bool checkMate = true;
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
//				// cannot castle
//				if (!Castle.empty()) continue;
//
//				if (!moveCheck(Board, color, piece, row_, col_, Captured)) { // if not in check after move (valid)
//					checkMate = false;
//					getScores(Board, piece, nextColor, depth - 1, row_, col_, Captured, totalMoves, "");
//				}
//			}
//		}
//		if (checkMate) {
//			// add one to moves and return since the game is over
//			totalMoves++;
//			return;
//		}
//	}
//
//	// here only the king is allowed to move
//	else if (moves == 2) {
//		std::string className = Board.IndClass[kingInd - 1];
//
//		// gets its row and column
//		std::pair<int, int> newCords = Board.PieceLoc[kingInd];
//
//		int row = newCords.first;
//		int col = newCords.second;
//
//		std::vector<std::tuple<int, int, bool, std::string>> moves = posMoves(className, row, col, color, Board);
//
//		bool checkMate = true;
//		for (auto move : moves) {
//			int row_ = std::get<0>(move);
//			int col_ = std::get<1>(move);
//			bool Captured = std::get<2>(move);
//			std::string Castle = std::get<3>(move);
//
//			// cannot castle
//			if (!Castle.empty()) continue;
//
//			if (!moveCheck(Board, color, kingInd, row_, col_, Captured)) { // if not in check after move (valid)
//				checkMate = false;
//				getScores(Board, kingInd, nextColor, depth - 1, row_, col_, Captured, totalMoves, "");
//			}
//		}
//		if (checkMate) {
//			// add one to moves and return since the game is over
//			totalMoves++;
//			return;
//		}
//	}
//	//     no check to worry about
//	else {
//
//		// class of piece
//		for (auto piece : pieces) {
//			std::string className = Board.IndClass[piece - 1];
//
//			// gets its row and column
//			std::pair<int, int> NewCords = Board.PieceLoc[piece];
//
//			int row1 = NewCords.first;
//			int col1 = NewCords.second;
//
//			std::vector<std::tuple<int, int, bool, std::string>> Moves = posMoves(className, row1, col1, color, Board); // , Board.renderer
//
//			// iterate through all of the moves
//			for (auto move : Moves) {
//				int row_ = std::get<0>(move);
//				int col_ = std::get<1>(move);
//				bool Captured = std::get<2>(move);
//				std::string Castle = std::get<3>(move);
//
//				getScores(Board, piece, nextColor, depth - 1, row_, col_, Captured, totalMoves, Castle);
//
//			}
//		}
//	}
//
//}
//

int ai::kingAttacks(board b, piece Piece) {

	// moves that can attack the king
	int killingMoves = 0;

	// sets variables of the piece
	auto Class = Piece.type;
	Color color = Piece.color;

	row Row = Piece.curRow;
	col Col = Piece.curCol;

	auto Board = b.boardArr;

    if (color == white) {

        row newRow = Row - 1;
        col newCol = Col + 1;

        // checks the attacks it can do
        if (Board[newRow][newCol].color == black && Board[newRow][newCol].type == PAWN ) {
            killingMoves++;
            if (killingMoves >= 2) return 2;
        }

        newRow = Row - 1;
        newCol = Col - 1;
        if (Board[newRow][newCol].color == black && Board[newRow][newCol].type == PAWN ) {
            killingMoves++;
            if (killingMoves >= 2) return 2;
        }
    }
    // black
    else {
        row newRow = Row + 1;
        row newCol = Col + 1;
        // checks the attacks it can do
        if (Board[newRow][newCol].color == white && Board[newRow][newCol].type == PAWN ) {
            killingMoves++;
            if (killingMoves >= 2) return 2;
        }

        newRow = Row + 1;
        newCol = Col - 1;
        if (Board[newRow][newCol].color == white && Board[newRow][newCol].type == PAWN ) {
            killingMoves++;
            if (killingMoves >= 2) return 2;
        }

    }
	/// rooks
	// loop through all the possible moves a rook can move up/down/left/right
	row newRow;
    col newCol;

    // boolean variables to determine whether we should continue going a specific direction
    // this is useful because if it is going up and sees an obstacle it can not go up further
    // so this is the indicator to not go up anymore
    bool goUp = true;
    bool goDown = true;
    bool goRight = true;
    bool goLeft = true;

    // vector of all possible moves here (could be illegal)
    std::vector<std::pair<int, int>> moves;

    for (int i = 1; i <= 8; i++) {

        // up
        newRow = Row - i;
        newCol = Col;

        // add to moves vector
        moves.emplace_back(newRow, newCol);

        // down
        newRow = Row + i;
        newCol = Col;

        moves.emplace_back(newRow, newCol);

        // right
        newRow = Row;
        newCol = Col + i;

        moves.emplace_back(newRow, newCol);

        // left
        newRow = Row;
        newCol = Col - i;

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
        if (Board[newRow][newCol].type != NONE){
            if (Board[newRow][newCol].color != color && Board[newRow][newCol].type == ROOK){
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

    /// horses

    moves.clear();

    // variables needed
    int col_down1 = Col + 1;
    int col_down2 = Col + 2;
    int col_up1 = Col - 1;
    int col_up2 = Col - 2;

    int row_right1 = Row + 1;
    int row_right2 = Row + 2;
    int row_left1 = Row - 1;
    int row_left2 = Row - 2;

    // adds all the moves
    moves.emplace_back(row_right1, col_down2);
    moves.emplace_back(row_left1, col_down2);

    moves.emplace_back(row_left2, col_down1);
    moves.emplace_back(row_left2, col_up1);

    moves.emplace_back(row_left1, col_up2);
    moves.emplace_back(row_right1, col_up2);

    moves.emplace_back(row_right2, col_up1);
    moves.emplace_back(row_right2, col_down1);

    newRow;
    newCol;
    for (std::pair<int, int> pair : moves) {
        newRow = pair.first;
        newCol = pair.second;

        // makes sure its in bounds
        if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) continue;

        // checks if the move is legal

        if (Board[newRow][newCol].color != color && Board[newRow][newCol].type == HORSE ){
            killingMoves++;
            if (killingMoves >= 2) return 2;
        }
    }
	/// king
	moves.clear();

    // adds all possible moves
    int new_col_up = Col - 1;
    int new_col_down = Col + 1;

    int new_row_left = Row - 1;
    int new_row_right = Row + 1;

    moves.emplace_back(Row, new_col_up);
    moves.emplace_back(Row, new_col_down);

    moves.emplace_back(new_row_right, Col);
    moves.emplace_back(new_row_left, Col);

    moves.emplace_back(new_row_right, new_col_down);
    moves.emplace_back(new_row_right, new_col_up);

    moves.emplace_back(new_row_left, new_col_down);
    moves.emplace_back(new_row_left, new_col_up);

    newRow;
    newCol;
    for (std::pair<int, int> pair : moves) {
        newRow = pair.first;
        newCol = pair.second;

        // makes sure its in bounds
        if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) continue;

        // checks if the move is legal

        if (Board[newRow][newCol].color != color && Board[newRow][newCol].type == KING){
            killingMoves++;
            if (killingMoves >= 2) return 2;
        }
    }

	/// queen
	// loop through all the possible moves a rook can move up/down/left/right

    // boolean variables to determine whether we should continue going a specific direction
    // this is useful because if it is going up and sees an obstacle it can not go up further
    // so this is the indicator to not go up anymore
    goUp = true;
    goDown = true;
    goRight = true;
    goLeft = true;
    bool goTopLeft = true;
    bool goBtmRight = true;
    bool goTopRight = true;
    bool goBtmLeft = true;

    // vector of all possible moves here (could be illegal)
    moves.clear();

    for (int i = 1; i <= 8; i++) {

        // up
        newRow = Row - i;
        newCol = Col;

        // add to moves vector
        moves.emplace_back(newRow, newCol);

        // down
        newRow = Row + i;
        newCol = Col;

        moves.emplace_back(newRow, newCol);

        // right
        newRow = Row;
        newCol = Col + i;

        moves.emplace_back(newRow, newCol);

        // left
        newRow = Row;
        newCol = Col - i;

        moves.emplace_back(newRow, newCol);

        // up left
        newRow = Row - i;
        newCol = Col - i;


        // add to moves vector
        moves.emplace_back(newRow, newCol);

        // down right
        newRow = Row + i;
        newCol = Col + i;

        moves.emplace_back(newRow, newCol);

        // down right
        newRow = Row - i;
        newCol = Col + i;

        moves.emplace_back(newRow, newCol);

        // down left
        newRow = Row + i;
        newCol = Col - i;

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
        if (Board[newRow][newCol].type != NONE){
            if (Board[newRow][newCol].color != color && Board[newRow][newCol].type == QUEEN){
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

	/// bishop
	// loop through all the possible moves a bishop can move up/down/left/right


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
        newRow = Row - i;
        newCol = Col - i;

        // add to moves vector
        moves.emplace_back(newRow, newCol);

        // down right
        newRow = Row + i;
        newCol = Col + i;

        moves.emplace_back(newRow, newCol);

        // down right
        newRow = Row - i;
        newCol = Col + i;

        moves.emplace_back(newRow, newCol);

        // down left
        newRow = Row + i;
        newCol = Col - i;

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
        if (Board[newRow][newCol].type != NONE){
            if (Board[newRow][newCol].color != color && Board[newRow][newCol].type == BISHOP){
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

U64 ai::perft(board b, int depth, bool print, Color color) {
    b.passentMoves.clear();

    // gets next color
    Color nextColor;

    if (color == white) nextColor = black;
    else nextColor = white;

    U64 nodes = 0;

    if (depth == 0)
        return 1;

    auto moves = allPosMoves(b, color);


    // find the king piece
    piece kingPiece;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (b.boardArr[i][j].type == KING && b.boardArr[i][j].color == color){
                kingPiece = b.boardArr[i][j];
            }
        }
    }
    // check all of opposite color's moves in case of check
    // moves correlates to the amount of pieces that can kill the king
    int kingMoves = kingAttacks(b,kingPiece);

    for (int i = 0; i < moves.size(); i++) {

        piece m = moves[i];

        if (!moveCheck(b, m, kingMoves)){
            continue;
        }

        if (depth == 1){
            nodes ++;
        }else{
            piece oldPiece = b.move(m);

            U64 np = perft(b, depth - 1, false, nextColor);

            if (print) {

                std::cout << m.toString() << " " << np << std::endl;
            }

            nodes += np;
            b.undoMove(m, oldPiece);
        }


    }

    return nodes;
}
bool ai::moveCheck(board b, const piece& Piece, int kingMoves) {
    // exceptions
    if (Piece.Castle != none) return false;

    // here only the king is allowed to move
    if (kingMoves == 2 && Piece.type != KING) return true;

    // does the move
    // changes the arrBoard
    b.boardArr[Piece.nextRow][Piece.nextCol] = Piece;

    // makes it empty
    b.boardArr[Piece.curRow][Piece.curCol] = piece();

    // find the king piece
    piece kingPiece;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (b.boardArr[i][j].type == KING && b.boardArr[i][j].color == Piece.color){
                kingPiece = b.boardArr[i][j];
                kingPiece.curCol = j;
                kingPiece.curRow = i;
            }
        }
    }

    int kingMoves2 = kingAttacks(b,kingPiece);

    if (kingMoves2 == 0){
        return true;
    }

    else return false;
}



// all the moves it will recursively call


// iterate through every possible move


