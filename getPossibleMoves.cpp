//
////
//// Created by zacky on 8/16/2021.
////
//
#include "getPossibleMoves.h"
std::vector<piece> allPosMoves(board b, Color color){
    std::vector<piece> moves;
    for (int i = 0; i < 8 ; i++){
        for (int j = 0; j < 8; j++){
            piece type = b.boardArr[j][i];
            if (type.color == color && type.type != NONE) posMoves(type, b, moves,everything);
        }
    }
    return moves;
}

// only gets the captures
std::vector<piece> allCaptures(board b, Color color){
    std::vector<piece> moves;
    for (int i = 0; i < 8 ; i++){
        for (int j = 0; j < 8; j++){
            piece type = b.boardArr[i][j];
            posMoves(type, b, moves, captures);
        }
    }
    return moves;
}

// only gets nonCaptures
std::vector<piece> noCaptures(board b, Color color){
    std::vector<piece> moves;
    for (int i = 0; i < 8 ; i++){
        for (int j = 0; j < 8; j++){
            piece type = b.boardArr[i][j];
            posMoves(type, b, moves, nonCaptures);
        }
    }
    return moves;
}

// directly adds moves to the moves vector in allPosMoves
void posMoves(piece Piece,board b, std::vector<piece> &allMoves, Mode mode) { // , SDL_Renderer* renderer

    // sets variables of the piece
    auto Class = Piece.type;
    Color color = Piece.color;

    row Row = Piece.curRow;
    col Col = Piece.curCol;

    auto Board = b.boardArr;

    // checks what class it is and gives the moves accordingly
    if (Class == PAWN) {
        if (color == black) {
            // checks if its on the starting row
            if (Row == 1) {
                // lets it moves two moves ahead

                // gets the cords of two moves ahead
                int newRow = Row + 2;
                int newCol = Col;

                if (Board[newRow][newCol].type == NONE && mode != captures){
                    // there is no piece on the square (move is legal)
                    // false at the end since it's not capturing a piece

                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    allMoves.push_back(newPiece);
                }
            }
            row newRow = Row + 1;
            col newCol = Col;

            if (Board[newRow][newCol].type == NONE && mode != captures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                allMoves.push_back(newPiece);
            }

            newRow = Row + 1;
            newCol = Col + 1;

            // checks the attacks it can do
            if (Board[newRow][newCol].color == white && Board[newRow][newCol].type != NONE && mode != nonCaptures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                newPiece.captured = true;

                allMoves.push_back(newPiece);
            }

            newRow = Row + 1;
            newCol = Col - 1;
            if (Board[newRow][newCol].color == white && Board[newRow][newCol].type != NONE && mode != nonCaptures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                newPiece.captured = true;

                allMoves.push_back(newPiece);
            }
        }
        // white
        else {
            // checks if its on the starting row
            if (Row == 6) {
                // lets it moves two moves ahead

                // gets the cords of two moves ahead
                int newRow = Row - 2;
                int newCol = Col;

                if (Board[newRow][newCol].type == NONE && mode != captures){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    allMoves.push_back(newPiece);
                }
            }
            row newRow = Row - 1;
            col newCol = Col;
            // checks one square in front
            if (Board[newRow][newCol].type == NONE && mode != captures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                allMoves.push_back(newPiece);
            }

            newRow = Row-1;
            newCol = Col + 1;
            // checks the attacks it can do
            if (Board[newRow][newCol].color == black && Board[newRow][newCol].type != NONE && mode != nonCaptures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                newPiece.captured = true;

                allMoves.push_back(newPiece);
            }

            newRow = Row-1;
            newCol = Col-1;
            if (Board[newRow][newCol].color == black && Board[newRow][newCol].type != NONE && mode != nonCaptures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                newPiece.captured = true;

                allMoves.push_back(newPiece);
            }

        }
    }
    // rooks
    if (Class == ROOK) {
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

            // if there is nothing in the square
            if (Board[newRow][newCol].type == NONE && mode != captures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                allMoves.push_back(newPiece);
            }
            // if there is a piece on the square
            if (Board[newRow][newCol].type != NONE && mode != nonCaptures){
                if (Board[newRow][newCol].color != color){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    newPiece.captured = true;

                    allMoves.push_back(newPiece);
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
        // castling

        // for white
        if (color == white){
            // left
            if (b.whiteCastleLeft){
                // check if both pieces haven't been captured
                bool first = Board[7][0].color == white && Board[7][0].type == ROOK ;
                bool second = Board[7][4].color == white && Board[7][4].type == KING;

                // two squares between them are empty
                bool third = Board[7][1].type == NONE;
                bool fourth = Board[7][2].type == NONE;
                bool fifth = Board[7][3].type == NONE;

                // if all are true
                if (first && second && third && fourth && fifth){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.Castle = whiteCastleLeft;

                    allMoves.push_back(newPiece);
                }
            }
            if (b.whiteCastleRight){
                // check if both pieces haven't been captured
                bool first = Board[7][7].color == white && Board[7][7].type == ROOK ;
                bool second = Board[7][4].color == white && Board[7][4].type == KING;

                // two squares between them are empty
                bool third = Board[7][5].type == NONE;
                bool fourth = Board[7][6].type == NONE;

                // if all are true
                if (first && second && third && fourth){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.Castle = whiteCastleRight;

                    allMoves.push_back(newPiece);
                }
            }
        }
        // black
        else{
            // left
            if (b.blackCastleLeft){
                // check if both pieces haven't been captured
                bool first = Board[0][0].color == black && Board[0][0].type == ROOK ;
                bool second = Board[0][4].color == black && Board[0][4].type == KING;

                // two squares between them are empty
                bool third = Board[0][1].type == NONE;
                bool fourth = Board[0][2].type == NONE;
                bool fifth = Board[0][3].type == NONE;

                // if all are true
                if (first && second && third && fourth && fifth){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.Castle = blackCastleLeft;

                    allMoves.push_back(newPiece);
                }
            }
            if (b.blackCastleRight){
                // check if both pieces haven't been captured
                bool first = Board[0][7].color == black && Board[0][7].type == ROOK ;
                bool second = Board[0][4].color == black && Board[0][4].type == KING;

                // two squares between them are empty
                bool third = Board[0][5].type == NONE;
                bool fourth = Board[0][6].type == NONE;

                // if all are true
                if (first && second && third && fourth){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.Castle = blackCastleRight;

                    allMoves.push_back(newPiece);
                }
            }
        }
    }
    else if (Class == HORSE) {
        // vector of all possible moves here (could be illegal)
        std::vector<std::pair<int, int>> moves;

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

        int newRow;
        int newCol;
        for (std::pair<int, int> pair : moves) {
            newRow = pair.first;
            newCol = pair.second;

            // makes sure its in bounds
            if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) continue;

            // checks if the move is legal

            if (Board[newRow][newCol].type == NONE && mode != captures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                allMoves.push_back(newPiece);
            }

            if (Board[newRow][newCol].color != color && Board[newRow][newCol].type != NONE && mode != nonCaptures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                newPiece.captured = true;

                allMoves.push_back(newPiece);
            }
        }
    }
    else if (Class == KING) {
        // vector of all possible moves here (could be illegal)
        std::vector<std::pair<int, int>> moves;

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

        int newRow;
        int newCol;
        for (std::pair<int, int> pair : moves) {
            newRow = pair.first;
            newCol = pair.second;

            // makes sure its in bounds
            if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) continue;

            // checks if the move is legal


            if (Board[newRow][newCol].type == NONE && mode != captures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                allMoves.push_back(newPiece);
            }
            if (Board[newRow][newCol].color != color && Board[newRow][newCol].type != NONE && mode != nonCaptures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                newPiece.captured = true;

                allMoves.push_back(newPiece);
            }
        }

    }
    else if (Class == QUEEN) {
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

            // if there is nothing in the square
            if (Board[newRow][newCol].type == NONE && mode != captures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                allMoves.push_back(newPiece);
            }

            // if there is a piece on the square
            if (Board[newRow][newCol].type != NONE && mode != nonCaptures){
                if (Board[newRow][newCol].color != color){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    newPiece.captured = true;

                    allMoves.push_back(newPiece);
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

    else if (Class == BISHOP) {
        // loop through all the possible moves a bishop can move up/down/left/right
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

            // if there is nothing in the square
            if (Board[newRow][newCol].type == NONE && mode != captures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                allMoves.push_back(newPiece);
            }
            // if there is a piece on the square
            if (Board[newRow][newCol].type != NONE && mode != nonCaptures){
                if (Board[newRow][newCol].color != color){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    newPiece.captured = true;

                    allMoves.push_back(newPiece);
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
    //
    //	for (std::tuple<int, int,bool> pair : moves) {
    //	    SDL_Rect rect{ std::get<1>(pair) * inter + inter / 4 ,std::get<0>(pair) * inter + inter / 4 , inter / 4, inter / 4 };
    //		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    //		SDL_RenderFillRect(renderer, &rect);
    //	}


    //	SDL_RenderPresent(renderer);
}