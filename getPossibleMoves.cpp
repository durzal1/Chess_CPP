//
// Created by zacky on 8/16/2021.
//

#include "getPossibleMoves.h"


std::vector<std::pair<int, int>> posMoves(std::string Class, int row, int col, std::string color, std::map<std::pair<int, int>, int> BoardLoc, int inter, SDL_Renderer* renderer) {
	// vector with all legal moves
	std::vector<std::pair<int, int>> possibleMoves;

	// checks what class it is and gives the moves accordingly
	if (Class == "pawn") {
		if (color == "black") {
			// checks if its on the starting row
			if (row == 1) {
				// lets it moves two moves ahead

				// gets the cords of two moves ahead
				int newRow = row + 2;
				int newCol = col;

				if (BoardLoc.find({ newRow,newCol }) == BoardLoc.end()) {
					// there is no piece on the square (move is legal)
					possibleMoves.emplace_back(newRow, newCol);
				}
			}
			// checks one square in front
			if (BoardLoc.find({ row + 1 ,col }) == BoardLoc.end()) {
				possibleMoves.emplace_back(row + 1, col);
			}

			// checks the attacks it can do
			if (BoardLoc.find({ row + 1 ,col + 1 }) != BoardLoc.end()) {
				// there is a piece there, so now we check if it's the enemies

				// get the index of the piece
				int index = BoardLoc[{row + 1, col + 1}];

				// checks if its white
				if (index > 16) {
					// legal move
					possibleMoves.emplace_back(row + 1, col + 1);
				}
			}
			if (BoardLoc.find({ row + 1 ,col - 1 }) != BoardLoc.end()) {
				// get the index of the piece
				int index = BoardLoc[{row + 1, col - 1}];

				// checks if its white
				if (index > 16) {
					// legal move
					possibleMoves.emplace_back(row + 1, col - 1);
				}
			}
		}
		// white
		else {
			// checks if its on the starting row
			if (row == 6) {
				// lets it moves two moves ahead

				// gets the cords of two moves ahead
				int newRow = row - 2;
				int newCol = col;

				if (BoardLoc.find({ newRow,newCol }) == BoardLoc.end()) {
					// there is no piece on the square (move is legal)
					possibleMoves.emplace_back(newRow, newCol);
				}
			}
			// checks one square in front
			if (BoardLoc.find({ row - 1 ,col }) == BoardLoc.end()) {
				possibleMoves.emplace_back(row - 1, col);
			}

			// checks the attacks it can do
			if (BoardLoc.find({ row - 1 ,col + 1 }) != BoardLoc.end()) {
				// there is a piece there, so now we check if it's the enemies

				// get the index of the piece
				int index = BoardLoc[{row - 1, col + 1}];

				// checks if its black
				if (index <= 16) {
					// legal move
					possibleMoves.emplace_back(row - 1, col + 1);
				}
			}
			if (BoardLoc.find({ row - 1 ,col - 1 }) != BoardLoc.end()) {
				// get the index of the piece
				int index = BoardLoc[{row - 1, col - 1}];

				// checks if its white
				if (index <= 16) {
					// legal move
					possibleMoves.emplace_back(row - 1, col - 1);
				}
			}
		}
	}
	// rooks
	if (Class == "rook") {
		// loop through all the possible moves a rook can move up/down/left/right
		int newRow;
		int newCol;

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

			// if there is nothing in the square
			if (BoardLoc.find({ newRow,newCol }) == BoardLoc.end()) {
				possibleMoves.emplace_back(newRow, newCol);
			}
			// if there is a piece on the square
			else {
				// make sure its the enemies

				// get the index
				int index = BoardLoc[{newRow, newCol}];

				// color
				std::string Color;

				if (index > 16) Color = "white";
				else Color = "black";

				if (color != Color) {
					// legal move since it is the enemy's piece
					possibleMoves.emplace_back(newRow, newCol);
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
	}
	else if (Class == "horse") {
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

			// checks if the move is legal
			if (BoardLoc.find({ newRow,newCol }) == BoardLoc.end()) {
				// open space
				possibleMoves.emplace_back(newRow, newCol);
			}
			else {
				// check if it's the enemy's piece

				// get the index
				int index = BoardLoc[{newRow, newCol}];

				// color
				std::string Color;

				if (index > 16) Color = "white";
				else Color = "black";

				if (color != Color) {
					// legal move since it is the enemy's piece
					possibleMoves.emplace_back(newRow, newCol);
				}
			}
		}
	}
	else if (Class == "king") {
		// vector of all possible moves here (could be illegal)
		std::vector<std::pair<int, int>> moves;

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

		int newRow;
		int newCol;
		for (std::pair<int, int> pair : moves) {
			newRow = pair.first;
			newCol = pair.second;

			// makes sure its in bounds
			if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) continue;

			// checks if the move is legal

			if (BoardLoc.find({ newRow,newCol }) == BoardLoc.end()) {
				// open space
				possibleMoves.emplace_back(newRow, newCol);
			}
			else {
				// check if it's the enemy's piece

				// get the index
				int index = BoardLoc[{newRow, newCol}];

				// color
				std::string Color;

				if (index > 16) Color = "white";
				else Color = "black";

				if (color != Color) {
					// legal move since it is the enemy's piece
					possibleMoves.emplace_back(newRow, newCol);
				}
			}
		}

	}
	else if (Class == "queen") {
		// loop through all the possible moves a rook can move up/down/left/right
		int newRow;
		int newCol;

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

		// vector of all possible moves here (could be illegal)
		std::vector<std::pair<int, int>> moves;

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
			// we do this by looking at the remainder (1 = up, 2 = down, 3 = right, 4 = left)
			Direction dir = Direction((i + 8) % 8);

			// check to see if we can keep going that direction
			if (dir == Up && !goUp || dir == Down && !goDown || dir == Right && !goRight || dir == Left && !goLeft || dir == topLeft && !goTopLeft|| dir == topRight && !goTopRight ||
				dir == bottomLeft && !goBtmLeft || dir == bottomRight && !goBtmRight) continue;

			// check if the move is legal
			bool legal = true;

			// if there is nothing in the square
			if (BoardLoc.find({ newRow,newCol }) == BoardLoc.end()) {
				possibleMoves.emplace_back(newRow, newCol);
			}
			// if there is a piece on the square
			else {
				// make sure its the enemies

				// get the index
				int index = BoardLoc[{newRow, newCol}];

				// color
				std::string Color;

				if (index > 16) Color = "white";
				else Color = "black";

				if (color != Color) {
					// legal move since it is the enemy's piece
					possibleMoves.emplace_back(newRow, newCol);
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
	}

	else if (Class == "bishop") {
		// loop through all the possible moves a rook can move up/down/left/right
		int newRow;
		int newCol;

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

			// if there is nothing in the square
			if (BoardLoc.find({ newRow,newCol }) == BoardLoc.end()) {
				possibleMoves.emplace_back(newRow, newCol);
			}
			// if there is a piece on the square
			else {
				// make sure its the enemies

				// get the index
				int index = BoardLoc[{newRow, newCol}];

				// color
				std::string Color;

				if (index > 16) Color = "white";
				else Color = "black";

				if (color != Color) {
					// legal move since it is the enemies piece
					possibleMoves.emplace_back(newRow, newCol);
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
	}

	for (std::pair<int, int> pair : possibleMoves) {
		SDL_Rect rect{ pair.second * inter + inter / 4 , pair.first * inter + inter / 4 , inter / 4, inter / 4 };
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &rect);
	}


	SDL_RenderPresent(renderer);
	return possibleMoves;
}