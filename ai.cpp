//
// Created by zacky on 8/16/2021.
//

#include "ai.h"

ai::ai(const board& b, int maxDepth, Color color, int timeLimit) {
    // honestly i dont even need this anymore lol

	// gets the max depth recursive function will go to
	this->maxDepth = maxDepth;

	this->timeLimit = timeLimit;
}


int ai::minMax(board b, int depth, Color color, int alpha, int beta, int &nodes, piece &bestMove, std::chrono::time_point<std::chrono::system_clock> start, std::vector<piece> &allMoves) {
    // checks to see if time ran out
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    // if time has ran out we set beta to -inf and alpha to inf to exit the recursive call
    if (duration.count() > timeLimit){
        if (color == black){
            alpha = 9999999;
            return alpha;
        }else{
            beta = -9999999;
            return beta;
        }
    }
    // gets next color
    Color nextColor;

    if (color == white) nextColor = black;
    else nextColor = white;

    if (depth == 0){
        // evaluate the move
        auto eval = evaluate();

        // sets value
        int whiteVal = 0;
        int blackVal = 0;
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if (b.boardArr[i][j].type != NONE){
                    if (b.boardArr[i][j].color == white){
                        whiteVal += b.getVal[b.boardArr[i][j].type];
                    }else{
                        blackVal += b.getVal[b.boardArr[i][j].type];
                    }
                }
            }
        }
        int val = whiteVal - blackVal;
        if (nextColor == black) val = blackVal - whiteVal;
        int valuation = eval.evaluateFunc(b,nextColor, val);

        return -valuation;
    }

    // also checks for en passant moves if there are any

    auto moves = allPosMoves(b, color);

    // resets old en passant moves and adds the new ones(if there are any)
    b.passentMoves.clear();

    U64 kingMoves = getKingMoves(b, color, moves[0], moves[1]);

    // for setting the best values gotten (minMax)
    int bestSoFar = -999999;
    bool go = false;
    for (int i = 0; i < moves.size(); i++) {
        auto &m = moves[i];
        if (!moveCheck(b, m, kingMoves)){

            continue;
        }
        nodes ++;
        piece oldPiece = b.move(m);

        // zobrist key of the current board
        zobVal zob = zobVal();

        U64 zobristKey = zob.getZob(b.boardArr, b.zobvals);

        if (b.boardArr[5][0].type == PAWN && b.boardArr[5][1].type == PAWN &&  b.boardArr[2][0].type == PAWN){
//            b.print();
            std::cout << 'f';
        }
        // score that the move will eventually lead to
        int value;

        // check if this move has already been computed.
        if (b.transpositionTable.count(zobristKey)){
            // key exists so we just make value the score(aka what it would have computed)
            auto val = b.transpositionTable.find(zobristKey);
            nodes --;
            value = val->second.score;
            std::cout << 'yeee';
        }else{
            // here no key exists so we manually compute the value and add it to the table
            value = -minMax(b, depth - 1, nextColor, -beta, -alpha, nodes, bestMove,start, allMoves);
            m.Value = value;

            b.transpositionTable.insert({zobristKey, TranspositionTable(zobristKey, value, depth, m)});
        }
        if (depth == maxDepth && value > bestSoFar){
            // reset the bestMove
            bestMove = m;
        }
        bestSoFar = std::max(value, bestSoFar);
        if (bestSoFar > beta){
            return bestSoFar;
        }

        alpha = std::max(alpha, bestSoFar);

        b.undoMove(m, oldPiece);

    }
    return bestSoFar;
}

int ai::kingAttacks(board b, const piece& Piece) {

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
        if (Board[newRow][newCol].color == black && Board[newRow][newCol].type == PAWN &&newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8 ) {
            killingMoves++;
            if (killingMoves >= 2) return 2;
        }

        newRow = Row - 1;
        newCol = Col - 1;
        if (Board[newRow][newCol].color == black && Board[newRow][newCol].type == PAWN&&newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8) {
            killingMoves++;
            if (killingMoves >= 2) return 2;
        }
    }
    // black
    else {
        row newRow = Row + 1;
        row newCol = Col + 1;
        // checks the attacks it can do
        if (Board[newRow][newCol].color == white && Board[newRow][newCol].type == PAWN &&newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8) {

            killingMoves++;
            if (killingMoves >= 2) return 2;
        }

        newRow = Row + 1;
        newCol = Col - 1;
        if (Board[newRow][newCol].color == white && Board[newRow][newCol].type == PAWN&&newRow < 8 && newRow >= 0 && newCol >= 0 && newCol < 8 ) {
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
U64 ai::getKingMoves(board &b, Color color, const piece& moves1, const piece& moves2){
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
    U64 kingMoves = kingAttacks(b,kingPiece);

    b.castleRight = false;
    b.castleLeft = false;
    // checks if we can move the king one spot right or left if they are at the default position
    // if we can move it then we can do the castle move on that side
    if (moves1.type == KING){
        if (moveCheck(b,moves1,kingMoves)){
            // can do this move
            if (moves1.nextCol == 3){
                // left
                b.castleLeft = true;
            }else{
                b.castleRight = true;
            }
        }
    }
    if (moves2.type == KING){
        if (moveCheck(b,moves2,kingMoves)){
            // can do this move
            if (moves2.nextCol == 3){
                // left
                b.castleLeft = true;
            }else{
                b.castleRight = true;
            }
        }
    }
    return (kingMoves);
}
U64 ai::perft(board b, int depth, bool print, Color color) {

    // gets next color
    Color nextColor;

    if (color == white) nextColor = black;
    else nextColor = white;

    U64 nodes = 0;
    if (depth == 0) return 1;

    // also checks for en passant moves if there are any

    auto moves = allPosMoves(b, color);

    // resets old en passant moves and adds the new ones(if there are any)
    b.passentMoves.clear();

    U64 kingMoves = getKingMoves(b, color, moves[0], moves[1]);

    for (int i = 0; i < moves.size(); i++) {

        piece m = moves[i];
        if (!moveCheck(b, m, kingMoves)){
            continue;
        }

        if (depth == 1){
            nodes ++;
            if (m.Castle != none)b.amountCastles ++;

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

    // here only the king is allowed to move
    if (kingMoves == 2 && (Piece.type != KING || Piece.Castle != none)) return false;

    // castle restrictions because of check
    else if (kingMoves == 1 && Piece.Castle != none) return false;
    else if ((Piece.Castle == whiteCastleLeft || Piece.Castle == blackCastleLeft) && !b.castleLeft) return false;
    else if ((Piece.Castle == whiteCastleRight || Piece.Castle == blackCastleRight) && !b.castleRight) return false;

    if (Piece.Castle != none){
        // does a castle
        if (Piece.Castle == whiteCastleLeft){
            // removing pieces
            b.boardArr[7][0] = piece();
            b.boardArr[7][4] = piece();

            // adding
            b.boardArr[7][2] = piece(7,2,KING, white);
            b.boardArr[7][3] = piece(7,3,ROOK, white);
        }
        else if (Piece.Castle == whiteCastleRight){
            // removing pieces
            b.boardArr[7][7] = piece();
            b.boardArr[7][4] = piece();

            // adding
            b.boardArr[7][6] = piece(7,6,KING, white);
            b.boardArr[7][5] = piece(7,5,ROOK, white);
        }else if (Piece.Castle == blackCastleRight){
            // removing pieces
            b.boardArr[0][7] = piece();
            b.boardArr[0][4] = piece();

            // adding
            b.boardArr[0][6] = piece(0,6,KING, black);
            b.boardArr[0][5] = piece(0,5,ROOK, black);
        }else if (Piece.Castle == blackCastleLeft){
            // removing pieces
            b.boardArr[0][0] = piece();
            b.boardArr[0][4] = piece();

            // adding
            b.boardArr[0][2] = piece(0,2,KING, black);
            b.boardArr[0][3] = piece(0,3,ROOK, black);
        }else{
            // something is wrong
            std::cout << "FIX CASTLE==============================================" << std::endl;
        }
    }
    else if (Piece.capRow != -1){
        // does an en passant move
        b.boardArr[Piece.nextRow][Piece.nextCol] = Piece;

        b.boardArr[Piece.curRow][Piece.curCol] = piece();
        b.boardArr[Piece.capRow][Piece.capCol] = piece();
    }
    else{
        // does a regular move
        // changes the arrBoard
        b.boardArr[Piece.nextRow][Piece.nextCol] = Piece;

        // makes it empty
        b.boardArr[Piece.curRow][Piece.curCol] = piece();
    }


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
    else{
        return false;
    }
}





// all the moves it will recursively call


// iterate through every possible move


