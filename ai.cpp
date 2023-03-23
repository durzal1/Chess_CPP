//
// Created by zacky on 8/16/2021.
//

#include "ai.h"

ai::ai(const board& b, int maxDepth, Color color, long long timeLimit) {
    // gets the max depth recursive function will go to
    this->maxDepth = maxDepth;

    this->timeLimit = timeLimit;
}
// zero window search
int ai::zwSearch(int beta, int depth,  board b, Color color, int &nodes) {
    // gets next color
    Color nextColor;

    if (color == white) nextColor = black;
    else nextColor = white;

    // this is either a cut- or all-node
    if( depth == 0 ) return qSearch(b, beta-1, beta, nextColor, nodes);

    piece p = piece(-22,-22,ROOK,white);

    std::vector<piece> essQueenMoves;

    // gets all the moves
//    auto moves = allPosMoves(b,color, p,essQueenMoves, everything);

    for (int i = 0; i < 9; i++) {
        nodes ++;
//        piece oldPiece = b.move(m);
        int score = -zwSearch(1-beta, depth - 1, b, nextColor, nodes);
//        b.undoMove(m, oldPiece);

        if(score >= beta){
            return beta;
        }
    }
    return beta-1;
    // todo this needs so much work like move sorting, only do legal moves, etc
}
int ai::Evaluate(board b, Color nextColor){
    // evaluate the move
    auto eval = evaluate();

    // sets value
    int whiteVal = 0;
    int blackVal = 0;
////    for (int i = 0; i < 8; i++){
////        for (int j = 0; j < 8; j++){
////            if (b.boardArr[i][j].type != NONE){
////                if (b.boardArr[i][j].color == white){
////                    whiteVal += b.getVal[b.boardArr[i][j].type];
////                }else{
////                    blackVal += b.getVal[b.boardArr[i][j].type];
////                }
////            }
////        }
////    }
    int val = whiteVal - blackVal;
    if (nextColor == black) val = blackVal - whiteVal;

    int valuation = eval.evaluateFunc(b,nextColor, val);

    return -valuation;
}
int ai::qSearch(board b, int alpha, int beta, Color color, int &nodes) {
    // gets next color
    Color nextColor;

    if (color == white) nextColor = black;
    else nextColor = white;

    int stand_pat = Evaluate(b, nextColor);

    if(stand_pat >= beta)
        return beta;

    if( alpha < stand_pat )
        alpha = stand_pat;

    piece p = piece(-22,-22,ROOK,white);

    std::vector<piece> essQueenMoves;

    // gets all the moves
    auto moves = allPosMoves(b,color, p,essQueenMoves, captures);

    for (auto & m : moves) {
        nodes ++;
//        piece oldPiece = b.move(m);
        int score = -qSearch(b, -beta, -alpha,nextColor, nodes);
//        b.undoMove(m, oldPiece);

        if( score >= beta )
            return beta;
        if( score > alpha )
            alpha = score;
    }
    return alpha;
}
int ai::pvSearch(board b, int depth, Color color, int alpha, int beta, int &nodes, piece &bestMove,std::chrono::time_point<std::chrono::system_clock> start, std::map<U64, TranspositionTable> &transpositionTable, piece firstMove){
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

//        auto f = qSearch(b, alpha, beta, color, nodes);
//        return f;
//        return Evaluate(b,nextColor);
    }

    // also checks for en passant moves if there are any


//     zob key of the og board
////    U64 ogZobKey = b.zobKeys.getZob(b.boardArr, b.zobVals);
    U64 ogZobKey = 1;

    // changes it based off of color
    if (color == white) ogZobKey +=1 ;
    else ogZobKey -= 1;

//    if (transpositionTable.count(ogZobKey)){
//        // key exists so we just make value the score(aka what it would have computed)
//        auto val1 = transpositionTable.find(ogZobKey);
//        int value1 = val1->second.score;
//
//        if (depth == maxDepth){
//            bestMove = val1->second.Move;
//        }
//
//        if (color == val1->second.Move.color && depth == val1->second.depth){
//            return value1;
//        }
//    }

    // essential queen moves that we need to check for castle purposes
    std::vector<piece> essQueenMoves;

    // if its the first iteration there will be no hash move(nor a need for it)

    std::vector<piece> moves;

    // sort the moves based off of their guess score


    // if there is a hashMove
    bool hasHashMove = true;

    piece hashMove;

    // finds the hash move
    if (transpositionTable.count(ogZobKey)){
        auto hash = transpositionTable.find(ogZobKey);
        hashMove = hash->second.Move;
    }

    if (hashMove.type == NONE ||hashMove.color != color){
        hasHashMove = false;
    }
    else{
        hashMove.curCol = hashMove.oldCol;
        hashMove.curRow = hashMove.oldRow;
    }


    moves = allPosMoves(b, color, hashMove, essQueenMoves, everything);

    // sort moves
    std::sort(moves.begin(), moves.end());

    if (hasHashMove) moves.insert(moves.begin(), hashMove);

    while (essQueenMoves.size() != 2)  essQueenMoves.emplace_back(-1,-1,PAWN, white);

    // resets old en passant moves and adds the new ones(if there are any)
    b.passentMoves.clear();

//    U64 kingMoves = getKingMoves(b, color, essQueenMoves[0], essQueenMoves[1]);

    // if there are more than 3 moves with the same score at the maxDepth then we dont use hash move for move ordering
    int countHash = 0;

    // this is the pair that will be added to the hashMoves hashmap
    std::tuple<U64, piece, int> addHash;



    // if it should fully search the move
    bool bSearchPv = true;

    // if it doesnt do any moves then its checkmate
    bool checkmate = true;

    for (auto & m : moves) {

        // if this is the first move then it will make it the first move Var
        if (depth == maxDepth) firstMove = m;

//        if (!moveCheck(b, m, kingMoves)){
//            continue;
//        }
        checkmate = false;

        nodes ++;
//        piece oldPiece = b.move(m);

        int value;

        if (bSearchPv){
            value = -pvSearch(b, depth - 1, nextColor, -beta, -alpha, nodes, bestMove,start, transpositionTable, firstMove);
        }
        else{
            value = -pvSearch(b, depth - 1, nextColor, -alpha-1, -alpha, nodes, bestMove,start, transpositionTable, firstMove);

            if (value > alpha){
                // has potential to be good so we redo the search
                value = -pvSearch(b, depth - 1, nextColor, -beta, -alpha, nodes, bestMove,start, transpositionTable, firstMove);
            }
        }

        // todo make sure the color is the board color
        if (value == 100003 || value == -100003 && b.playerTurn == color){
            firstMove.oldRow = firstMove.curRow;
            firstMove.oldCol = firstMove.curCol;

            bestMove = firstMove;

            if (color == black){
                alpha = 6666666;
                return alpha;
            }else{
                beta = -6666666;
                return beta;
            }
        }

        m.Value = value;

        if (value >= beta){
//            transpositionTable.insert({ogZobKey, TranspositionTable(ogZobKey, value, depth, std::get<1>(addHash))}); //todo add back

            if (depth == maxDepth){
                bestMove = std::get<1>(addHash);
            }
            return beta;
        }
        if (value > alpha){
            alpha = value;
            bSearchPv = false;
            addHash = {ogZobKey, m, value};
        }
//        b.undoMove(m, oldPiece);

    }
    if (depth == maxDepth){
        bestMove = std::get<1>(addHash);
    }

    transpositionTable.insert({ogZobKey, TranspositionTable(ogZobKey, alpha, depth, bestMove)});

    // returns arbitrary number that can not be made using regular means
    if (checkmate) alpha = 100003;

    return alpha;
}

U64 ai::perft(board b, int depth, bool print, Color color) {

    // gets next color
    Color nextColor;

    if (color == white){
        nextColor = black;
        b.playerTurn = color;
    }
    else{
        nextColor = white;
        b.playerTurn = color;
    }

    U64 nodes = 0;
    if (depth == 0) return 1;

    moveGen gen = moveGen(b.bitBoard, b.playerTurn, b.boardArr);

    moveList movelist = gen.genAll();


    for (int i = 0; i < movelist.getSize(); i++) {

        Move m = movelist.getMove(i);

        if (depth == 1){
            nodes ++;
        }else{
            b.move(m);

            U64 np = perft(b, depth - 1, false, nextColor);

            if (print) {
                movelist.toString(m, np);
            }
            nodes += np;
            b.undoMove(m);
        }


    }
    return nodes;
}



U64 ai::testTime(board b, int depth, bool print, Color color) {

    // gets next color
    Color nextColor;

    if (color == white){
        nextColor = black;
        b.playerTurn = color;
    }
    else{
        nextColor = white;
        b.playerTurn = color;
    }

    U64 nodes = 0;
    if (depth == 0) return 1;

    moveGen gen = moveGen(b.bitBoard, b.playerTurn, b.boardArr);

    moveList& movelist = gen.genAll();

    int val = 3200000;


    for (int i = 0; i < val; i++){
        gen = moveGen(b.bitBoard, b.playerTurn, b.boardArr);
        movelist = gen.genAll();

        for (int j = 0; j < movelist.getSize(); j++){

            auto m = movelist.getMove(j);
            b.move(m);
            b.undoMove(m);
        }


    }

    return val * movelist.getSize();
}
//bool ai::moveCheck(board b, const piece& Piece, int kingMoves) {
//
//    // here only the king is allowed to move
//    if (kingMoves == 2 && (Piece.type != KING || Piece.Castle != none)) return false;
//
//        // castle restrictions because of check
//    else if (kingMoves == 1 && Piece.Castle != none) return false;
//    else if ((Piece.Castle == whiteCastleLeft || Piece.Castle == blackCastleLeft) && !b.castleLeft) return false;
//    else if ((Piece.Castle == whiteCastleRight || Piece.Castle == blackCastleRight) && !b.castleRight) return false;
//
//    if (Piece.Castle != none){
//        // does a castle
//        if (Piece.Castle == whiteCastleLeft){
//            // removing pieces
//            b.boardArr[7][0] = piece();
//            b.boardArr[7][4] = piece();
//
//            // adding
//            b.boardArr[7][2] = piece(7,2,KING, white);
//            b.boardArr[7][3] = piece(7,3,ROOK, white);
//        }
//        else if (Piece.Castle == whiteCastleRight){
//            // removing pieces
//            b.boardArr[7][7] = piece();
//            b.boardArr[7][4] = piece();
//
//            // adding
//            b.boardArr[7][6] = piece(7,6,KING, white);
//            b.boardArr[7][5] = piece(7,5,ROOK, white);
//        }else if (Piece.Castle == blackCastleRight){
//            // removing pieces
//            b.boardArr[0][7] = piece();
//            b.boardArr[0][4] = piece();
//
//            // adding
//            b.boardArr[0][6] = piece(0,6,KING, black);
//            b.boardArr[0][5] = piece(0,5,ROOK, black);
//        }else if (Piece.Castle == blackCastleLeft){
//            // removing pieces
//            b.boardArr[0][0] = piece();
//            b.boardArr[0][4] = piece();
//
//            // adding
//            b.boardArr[0][2] = piece(0,2,KING, black);
//            b.boardArr[0][3] = piece(0,3,ROOK, black);
//        }else{
//            // something is wrong
//            std::cout << "FIX CASTLE==============================================" << std::endl;
//        }
//    }
//    else if (Piece.capRow != -1){
//        // does an en passant move
//        b.boardArr[Piece.nextRow][Piece.nextCol] = Piece;
//
//        b.boardArr[Piece.curRow][Piece.curCol] = piece();
//        b.boardArr[Piece.capRow][Piece.capCol] = piece();
//    }
//    else{
//        // does a regular move
//        // changes the arrBoard
//        b.boardArr[Piece.nextRow][Piece.nextCol] = Piece;
//
//        // makes it empty
//        b.boardArr[Piece.curRow][Piece.curCol] = piece();
//    }
//
//
//    // find the king piece
//    piece kingPiece;
//
//    for (int i = 0; i < 8; i++){
//        for (int j = 0; j < 8; j++){
//            if (b.boardArr[i][j].type == KING && b.boardArr[i][j].color == Piece.color){
//
//                kingPiece = b.boardArr[i][j];
//
//                kingPiece.curCol = j;
//                kingPiece.curRow = i;
//            }
//        }
//    }
//
//    int kingMoves2 = kingAttacks(b,kingPiece);
//
//    if (kingMoves2 == 0){
//        return true;
//    }
//    else{
//        return false;
//    }
//}






// all the moves it will recursively call


// iterate through every possible move