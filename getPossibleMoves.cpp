//
////
//// Created by zacky on 8/16/2021.
////
//
#include "getPossibleMoves.h"
std::vector<piece> allPosMoves(const board& b, Color color, const piece& hashMove, std::vector<piece> &essQueenMoves, Mode mode){
    std::vector<piece> moves;

    for (int i = 0; i < 8 ; i++){
        for (int j = 0; j < 8; j++){
            piece type = b.boardArr[j][i];

            type.curCol = i;
            type.curRow = j;
            if (type.color == color && type.type != NONE) posMoves(type, b, moves,mode, hashMove, essQueenMoves);
        }
    }
    return moves;
}

// only gets the captures
std::vector<piece> allCaptures(const board& b, Color color){
    std::vector<piece> essQueenMoves;

    std::vector<piece> moves;
    for (int i = 0; i < 8 ; i++){
        for (int j = 0; j < 8; j++){
            piece type = b.boardArr[i][j];

            type.curCol = i;
            type.curRow = j;
            if (type.color == color && type.type != NONE) posMoves(type, b, moves,captures, piece(-1, -1, ROOK, black), essQueenMoves);
        }
    }
    return moves;
}

// only gets nonCaptures
std::vector<piece> noCaptures(const board& b, Color color){
    std::vector<piece> moves;
    for (int i = 0; i < 8 ; i++){
        for (int j = 0; j < 8; j++){
            piece type = b.boardArr[i][j];
//            posMoves(type, b, moves, nonCaptures);
        }
    }
    return moves;
}

// directly adds moves to the moves vector in allPosMoves
void posMoves(const piece& Piece,const board& b, std::vector<piece> &allMoves, Mode mode, const piece& hashMove, std::vector<piece> &essQueenMoves) { // , SDL_Renderer* renderer

    // sets variables of the piece
    auto Class = Piece.type;
    Color color = Piece.color;

    row Row = Piece.curRow;
    col Col = Piece.curCol;

    auto getVal = b.getVal;
    // checks what class it is and gives the moves accordingly
    if (Class == PAWN) {
        if (color == black) {
            // checks if its on the starting row
            if (Row == 1) {
                // lets it moves two moves ahead

                // gets the cords of two moves ahead
                int newRow = Row + 2;
                int newCol = Col;

                if (b.boardArr[newRow][newCol].type == NONE && mode != captures && newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8 && b.boardArr[Row + 1][Col].type == NONE){
                    // there is no piece on the square (move is legal)
                    // false at the end since it's not capturing a piece

                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    // adds the temporary en passent
                    newPiece.rowPassant = Row + 1;
                    newPiece.colPassant = newCol;

                    // makes sure its not the hashMove
                    if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                    else allMoves.push_back(newPiece);

                }
            }
            // if any of these have a row of 7 they are going to promote
            // therefore we add four of them (horse, queen, rook, and bishop)
            // idk why we need rook and bishop but the pro programs do that so yea lol

            row newRow = Row + 1;
            col newCol = Col;

            if (b.boardArr[newRow][newCol].type == NONE && mode != captures && newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                // makes sure its not the hashMove
                if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                else{
                    if (newRow == 7){
                        newPiece.promotion = QUEEN;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = HORSE;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = BISHOP;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = ROOK;
                    }

                    allMoves.push_back(newPiece);
                }
            }

            newRow = Row + 1;
            newCol = Col + 1;

            // checks the attacks it can do
            if (b.boardArr[newRow][newCol].color == white && b.boardArr[newRow][newCol].type != NONE && mode != nonCaptures && newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                else{
                    newPiece.captured = true;

                    newPiece.moveOrdGrad += getVal[b.boardArr[newRow][newCol].type] - getVal[newPiece.type];
                    if (newPiece.moveOrdGrad >= 0)newPiece.moveOrdGrad += goodCapture;
                    else newPiece.moveOrdGrad += badCapture;

                    if (newRow == 7){
                        newPiece.promotion = QUEEN;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = HORSE;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = BISHOP;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = ROOK;
                    }

                    allMoves.push_back(newPiece);
                }

            }

            newRow = Row + 1;
            newCol = Col - 1;
            if (b.boardArr[newRow][newCol].color == white && b.boardArr[newRow][newCol].type != NONE && mode != nonCaptures && newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                newPiece.captured = true;
                newPiece.moveOrdGrad += getVal[b.boardArr[newRow][newCol].type] - getVal[newPiece.type];
                if (newPiece.moveOrdGrad >= 0)newPiece.moveOrdGrad += goodCapture;
                else newPiece.moveOrdGrad += badCapture;
                if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                else{
                    if (newRow == 7){
                        newPiece.promotion = QUEEN;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = HORSE;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = BISHOP;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = ROOK;
                    }

                    allMoves.push_back(newPiece);
                }

            }
            if (!b.passentMoves.empty()){
                // en passant moves
                newRow = Row + 1;
                newCol = Col + 1;

                if (b.boardArr[newRow][newCol].type == NONE && b.boardArr[Row][newCol].type == PAWN && b.boardArr[Row][newCol].color != color && b.passentMoves[0].first == newRow && b.passentMoves[0].second == newCol && newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                    else{
                        newPiece.captured = true;

                        newPiece.moveOrdGrad += getVal[b.boardArr[newRow][newCol].type] - getVal[newPiece.type];
                        if (newPiece.moveOrdGrad >= 0)newPiece.moveOrdGrad += goodCapture;
                        else newPiece.moveOrdGrad += badCapture;

                        newPiece.capRow = Row;
                        newPiece.capCol = newCol;
                        allMoves.push_back(newPiece);

                    }

                }

                newRow = Row + 1;
                newCol = Col - 1;
                if (b.boardArr[newRow][newCol].type == NONE && b.boardArr[Row][newCol].type == PAWN && b.boardArr[Row][newCol].color != color && b.passentMoves[0].first == newRow && b.passentMoves[0].second == newCol && newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                    else{
                        newPiece.captured = true;

                        newPiece.moveOrdGrad += getVal[b.boardArr[newRow][newCol].type] - getVal[newPiece.type];
                        if (newPiece.moveOrdGrad >= 0)newPiece.moveOrdGrad += goodCapture;
                        else newPiece.moveOrdGrad += badCapture;

                        newPiece.capRow = Row;
                        newPiece.capCol = newCol;
                        allMoves.push_back(newPiece);

                    }

                }
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

                if (b.boardArr[newRow][newCol].type == NONE && mode != captures && newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8 && b.boardArr[Row - 1][Col].type == NONE){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    // adds the temporary en passent
                    newPiece.rowPassant = Row - 1;
                    newPiece.colPassant = newCol;

                    if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                    else allMoves.push_back(newPiece);
                }
            }
            row newRow = Row - 1;
            col newCol = Col;
            // checks one square in front
            if (b.boardArr[newRow][newCol].type == NONE && mode != captures && newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                else{
                    if (newRow == 0){
                        newPiece.promotion = QUEEN;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = HORSE;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = BISHOP;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = ROOK;
                    }

                    allMoves.push_back(newPiece);
                }
            }

            newRow = Row-1;
            newCol = Col + 1;
            // checks the attacks it can do
            if (b.boardArr[newRow][newCol].color == black && b.boardArr[newRow][newCol].type != NONE && mode != nonCaptures && newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                newPiece.captured = true;

                newPiece.moveOrdGrad += getVal[b.boardArr[newRow][newCol].type] - getVal[newPiece.type];
                if (newPiece.moveOrdGrad >= 0)newPiece.moveOrdGrad += goodCapture;
                else newPiece.moveOrdGrad += badCapture;

                if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                else{
                    if (newRow == 0){
                        newPiece.promotion = QUEEN;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = HORSE;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = BISHOP;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = ROOK;
                    }

                    allMoves.push_back(newPiece);
                }
            }

            newRow = Row-1;
            newCol = Col-1;
            if (b.boardArr[newRow][newCol].color == black && b.boardArr[newRow][newCol].type != NONE && mode != nonCaptures && newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                newPiece.captured = true;

                newPiece.moveOrdGrad += getVal[b.boardArr[newRow][newCol].type] - getVal[newPiece.type];
                if (newPiece.moveOrdGrad >= 0)newPiece.moveOrdGrad += goodCapture;
                else newPiece.moveOrdGrad += badCapture;

                if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                else{
                    if (newRow == 0){
                        newPiece.promotion = QUEEN;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = HORSE;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = BISHOP;
                        allMoves.push_back(newPiece);
                        newPiece.promotion = ROOK;
                    }

                    allMoves.push_back(newPiece);
                }
            }
            if (!b.passentMoves.empty()){
                // en passant attacks
                newRow = Row-1;
                newCol = Col + 1;
                // checks if this move is an en passant move
                if (b.boardArr[newRow][newCol].type == NONE && b.boardArr[Row][newCol].type == PAWN && b.boardArr[Row][newCol].color != color && b.passentMoves[0].first == newRow && b.passentMoves[0].second == newCol && newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    newPiece.captured = true;

                    newPiece.moveOrdGrad += getVal[b.boardArr[newRow][newCol].type] - getVal[newPiece.type];
                    if (newPiece.moveOrdGrad >= 0)newPiece.moveOrdGrad += goodCapture;
                    else newPiece.moveOrdGrad += badCapture;

                    newPiece.capRow = Row;
                    newPiece.capCol = newCol;

                    if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                    else allMoves.push_back(newPiece);
                }

                newRow = Row-1;
                newCol = Col-1;
                if (b.boardArr[newRow][newCol].type == NONE && b.boardArr[Row][newCol].type == PAWN && b.boardArr[Row][newCol].color != color && b.passentMoves[0].first == newRow && b.passentMoves[0].second == newCol && newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    newPiece.captured = true;

                    newPiece.moveOrdGrad += getVal[b.boardArr[newRow][newCol].type] - getVal[newPiece.type];
                    if (newPiece.moveOrdGrad >= 0)newPiece.moveOrdGrad += goodCapture;
                    else newPiece.moveOrdGrad += badCapture;

                    newPiece.capRow = Row;
                    newPiece.capCol = newCol;

                    if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                    else allMoves.push_back(newPiece);


                }
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
            if (b.boardArr[newRow][newCol].type == NONE && mode != captures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;
                if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol && newPiece.type == hashMove.type);
                else{
                    // looks for castles
                    if (color == white){
                        // valid castles
                        if (b.WhiteCastleLeft && newCol == 3 && newRow == 7 && Row == 7 && Col == 0){
                            allMoves.push_back(newPiece);
                            newPiece.Castle = whiteCastleLeft;
                        }
                        else if (b.WhiteCastleRight && newCol == 5 && newRow == 7 && Row == 7 && Col == 7){
                            allMoves.push_back(newPiece);
                            newPiece.Castle = whiteCastleRight;
                        }
                    }else{
                        if (b.BlackCastleLeft && newCol == 3 && newRow == 0 && Row == 0 && Col == 0){
                            allMoves.push_back(newPiece);
                            newPiece.Castle = blackCastleLeft;
                        }
                        else if (b.BlackCastleRight && newCol == 5 && newRow == 0 && Row == 0 && Col == 7){
                            allMoves.push_back(newPiece);
                            newPiece.Castle = blackCastleRight;
                        }
                    }

                    allMoves.push_back(newPiece);
                }

            }
            // if there is a piece on the square
            if (b.boardArr[newRow][newCol].type != NONE && mode != nonCaptures){
                if (b.boardArr[newRow][newCol].color != color){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    newPiece.captured = true;

                    newPiece.moveOrdGrad += getVal[b.boardArr[newRow][newCol].type] - getVal[newPiece.type];
                    if (newPiece.moveOrdGrad >= 0)newPiece.moveOrdGrad += goodCapture;
                    else newPiece.moveOrdGrad += badCapture;

                    if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                    else allMoves.push_back(newPiece);
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

            if (b.boardArr[newRow][newCol].type == NONE && mode != captures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                else allMoves.push_back(newPiece);
            }

            if (b.boardArr[newRow][newCol].color != color && b.boardArr[newRow][newCol].type != NONE && mode != nonCaptures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                newPiece.captured = true;

                newPiece.moveOrdGrad += getVal[b.boardArr[newRow][newCol].type] - getVal[newPiece.type];
                if (newPiece.moveOrdGrad >= 0)newPiece.moveOrdGrad += goodCapture;
                else newPiece.moveOrdGrad += badCapture;

                if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                else allMoves.push_back(newPiece);
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

            // bool for castle parameter
            // checks if it can move left or right successfully if its in the default spot
            bool castleParam = false;

            if (color == white){
                if (newCol == 3 && newRow == 7 && Col == 4 && Row == 7){
                    castleParam = true;
                }else if (newCol == 5 && newRow == 7&& Col == 4 && Row == 7 ) castleParam = true;
            }else{
                if (newCol == 3 && newRow == 0 && Col == 4 && Row == 0){
                    castleParam = true;
                }else if (newCol == 5 && newRow == 0 && Col == 4 && Row == 0 ) castleParam = true;
            }

            if (b.boardArr[newRow][newCol].type == NONE && mode != captures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                if (castleParam){
                    essQueenMoves.push_back(newPiece);
                }
                if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                else allMoves.push_back(newPiece);
            }
            if (b.boardArr[newRow][newCol].color != color && b.boardArr[newRow][newCol].type != NONE && mode != nonCaptures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                newPiece.captured = true;

                newPiece.moveOrdGrad += getVal[b.boardArr[newRow][newCol].type] - getVal[newPiece.type];
                if (newPiece.moveOrdGrad >= 0)newPiece.moveOrdGrad += goodCapture;
                else newPiece.moveOrdGrad += badCapture;

                if (castleParam) essQueenMoves.push_back(newPiece);

                if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                else allMoves.push_back(newPiece);
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
            if (b.boardArr[newRow][newCol].type == NONE && mode != captures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                else allMoves.push_back(newPiece);
            }

            // if there is a piece on the square
            if (b.boardArr[newRow][newCol].type != NONE && mode != nonCaptures){
                if (b.boardArr[newRow][newCol].color != color){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    newPiece.captured = true;

                    newPiece.moveOrdGrad += getVal[b.boardArr[newRow][newCol].type] - getVal[newPiece.type];
                    if (newPiece.moveOrdGrad >= 0)newPiece.moveOrdGrad += goodCapture;
                    else newPiece.moveOrdGrad += badCapture;

                    if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                    else allMoves.push_back(newPiece);
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
            if (b.boardArr[newRow][newCol].type == NONE && mode != captures){
                // create a copy of the piece
                piece newPiece = piece(Piece);

                // adjust the new Piece
                newPiece.nextCol = newCol;
                newPiece.nextRow = newRow;

                if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                else allMoves.push_back(newPiece);
            }
            // if there is a piece on the square
            if (b.boardArr[newRow][newCol].type != NONE && mode != nonCaptures){
                if (b.boardArr[newRow][newCol].color != color){
                    // create a copy of the piece
                    piece newPiece = piece(Piece);

                    // adjust the new Piece
                    newPiece.nextCol = newCol;
                    newPiece.nextRow = newRow;

                    newPiece.captured = true;

                    newPiece.moveOrdGrad += getVal[b.boardArr[newRow][newCol].type] - getVal[newPiece.type];
                    if (newPiece.moveOrdGrad >= 0)newPiece.moveOrdGrad += goodCapture;
                    else newPiece.moveOrdGrad += badCapture;

                    if (newPiece.curCol == hashMove.oldCol && newPiece.curRow == hashMove.oldRow && newPiece.nextRow == hashMove.nextRow && newPiece.nextCol == hashMove.nextCol);
                    else allMoves.push_back(newPiece);
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