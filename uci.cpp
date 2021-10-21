//
// Created by zacky on 9/3/2021.
//

#include "uci.h"
#include "math.h"
#include "algorithm"
void uci::mainloop() {
    std::cout << "Durzal's Master Piece" << std::endl;

    std::string line = "";
//    uci::processCommand(line);

    while (std::getline(std::cin, line)){
        uci::processCommand(line);
    }
}
void uci::processCommand(std::string str) {
    // get each part of the string seperated
    std::vector<std::string> split = uci::getSeperate(str);

    if (split[0] == "go"){
        // here im only going to do this for wtime etc
        // but idc what it gives cuz im going to give each move 5 seconds to do it

        // either you go infinite for x time or to a specific depth

        // set depth to 20 cuz thats basically infinity
        int depth = 20;

        // sets the time to infinity
        int wtime = 999999999;
        int btime = 999999999;

        // sets incrememnt to 0
        int winc = 0;
        int binc = 0;

        // turns will be 40 by default
        int turns = 40;

        // time will be 5 seconds by default
        long long timeLimit = 5000;

        if (split.size() > 1){
            if (split[1] == "depth") depth = split[2][0] - '0';
            else if (split[1] == "wtime"){
                // converts the string times to int values
                wtime = 0;
                int size = split[2].size();
                for (int i = size; i >= 0; i--){
                    int mult = pow(10,i-1);
                    int num = split[2][size - i] - '0';
                    wtime += num * mult;
                }

                btime = 0;
                size = split[4].size();
                for (int i = size; i >= 0; i--){
                    int mult = pow(10,i-1);
                    int num = split[4][size - i] - '0';
                    btime += num * mult;
                }

                // if there is an increment
                if (split[5] == "winc"){
                    // sets the incrememnt
                    winc = 0;
                    int size = split[6].size();
                    for (int i = size; i >= 0; i--){
                        int mult = pow(10,i-1);
                        int num = split[6][size - i] - '0';
                        winc += num * mult;
                    }

                    binc = 0;
                    size = split[8].size();
                    for (int i = size; i >= 0; i--){
                        int mult = pow(10,i-1);
                        int num = split[8][size - i] - '0';
                        binc += num * mult;
                    }

                    // gets the turns left
                    turns = 0;
                    size = split[10].size();
                    for (int i = size; i >= 0; i--){
                        int mult = pow(10,i-1);
                        int num = split[10][size - i] - '0';
                        turns += num * mult;
                    }
                }
                else{
                    // gets the turns left
                    turns = 0;
                    size = split[6].size();
                    for (int i = size; i >= 0; i--){
                        int mult = pow(10,i-1);
                        int num = split[6][size - i] - '0';
                        turns += num * mult;
                    }
                }


                // sets the timeLimit
                if (Board.playerTurn == black) timeLimit = btime / 40;
                else timeLimit = wtime / 40 ;
            }
        }

        uci::go(depth, timeLimit);
    }else if (split[0] == "position"){
        // gets needed values
        std::string fen;
        std::string moves;

        if (split[1] == "startpos"){

            fen = Default;
            uci::position_fen(fen);

            Board.playerTurn = white;
            if (split.size() > 2){
                for (int i = 3; i < split.size(); i++){
                    if (Board.playerTurn == white) Board.playerTurn = black;
                    else Board.playerTurn = white;
                    uci::moves(split[i]);
                }
            }
        }else if (split[1] == "fen"){
            // get the fen pos
            fen = split[2]+ " " + split[3]+ " " +split[4] + " " + split[5];
            uci::position_fen(fen);

            // reset the color
            Board.playerTurn = white;

            // do the moves and change color
            if (split.size() > 8){
                for (int i = 9; i < split.size(); i++){
                    if (Board.playerTurn == white) Board.playerTurn = black;
                    else Board.playerTurn = white;
                    uci::moves(split[i]);
                }
            }
        }
//        if (split.size() >=10){
//            fen = split[2]+ " " + split[3]+ " " +split[4] + " " + split[5];
//            moves = split[9];
//        }


    }else if (split[0] == "setoption"){
        // gets needed values
//        std::string name = split[2];
//        std::string value = split[4];
//
//        uci::set_option(name, value);
    }else if (split[0] == "isready"){
        uci::isReady();
    }else if (split[0] == "stop"){
        uci::stop();
    }else if (split[0] == "print"){
        uci::print();
    }else if (split[0] == "uci"){
        uci::Uci();
    }else if (split[0] == "ucinewgame"){
        Board = board(Default);
    }
}
void uci::go(int depth, long long timeLimit) {
    // does iterative deepening and if it runs out of time it will set beta to -inf and alpha to inf
    // then it will use best move from the last iteration
    auto start = std::chrono::high_resolution_clock::now();

    timeLimit = 999999999999;

    ai AI = ai(Board, 1, Board.playerTurn, timeLimit);


    // the last best move (for when we run out of time and stop the current one)
    piece lastBestMove = piece();

    // used to subtract from the last node amount (to get an accurate node amount)
    int lastNode = 0;

    // move list that was made from the previous iteration (1 ply will have a default move list)

    // the next move list that is being made in the current iteration
    std::map<std::pair<std::pair<row, col>, std::pair<row,col>>, piece> nextMoveList;

    // the moves that have been done in the current recursive iteration
    std::vector<piece> movesDone;

    std::map<U64, TranspositionTable> transpositionTable;


    for (int i = 1; i <= depth; i++){

        // sets the hash moves of the current iteration and then deletes them so they can store the new ones
        std::map<U64, TranspositionTable>::iterator it;

        nextMoveList.clear();

        int nodes = 0;

        AI.maxDepth = i;
        piece bestMove = piece();


        piece firstMove;

        // todo make it so that it only stops when there is no captures left
        //  first we create a hash to hold all the best moves (hash moves) DONE
        //  for all the captures we grade them by mllVVa
        //  the killers we will hold them in a hash map similar to hash moves but returns a killer (if there is one)


        int score = AI.pvSearch(Board, i, Board.playerTurn,-999999, 999999, nodes, bestMove, start, transpositionTable, firstMove);

        // check mate so we just end early
        if (score == 6666666 || score == -6666666){
            lastBestMove = bestMove;
            break;
        }
        // checks to makes sure it didnt leave too early
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        // didnt leave to early so we replace the lastBestMove
        if (duration.count() <= timeLimit){
            auto du = duration.count();

            std::chrono::milliseconds dur(du);

            std::chrono::time_point<std::chrono::system_clock> dt(dur);
            lastNode += nodes;

            double time = double(du) / 1000;
            int nps = nodes / time;
            std::cout << "info depth " << i << " score cp "  << score << " nodes " << lastNode <<  " nps " << nps << " time " << duration.count() << " ";
            std::cout << "PV ";
            for (piece p:bestMove.pastMoves){
                std::cout << p.toString() << " ";
            }
            std::cout << "" << std::endl;

            lastBestMove = bestMove;
        }
        else break;

    }
    lastBestMove.curCol = lastBestMove.oldCol;
    lastBestMove.curRow = lastBestMove.oldRow;
    std::cout << "bestmove" << " " << lastBestMove.toString() << std::endl;

}
void uci::set_option(std::string &name, std::string &value) {

}
void uci::position_fen(std::string fen) {
    // sets up the board
    Board.FENboard(fen);
    Board.setBitset();
}
void uci::stop() {
    std::cout << "STOP" << std::endl;
}
void uci::isReady() {
    std::cout << "readyok" << std::endl;
}
std::vector<std::string> uci::getSeperate(std::string str) {
    std::vector<std::string> split;
    std::string delimiter = " ";

    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        str.erase(0, pos + delimiter.length());
        split.push_back(token);
    }
    split.push_back(str);
    return split;
}

uci::uci() {
    Board = board(Default);
}

void uci::print() {
    Board.print();
    std::cout << Color(Board.playerTurn) << std::endl;
}

void uci::Uci() {
    std::cout << "id name Toman " << "1" << "." << "0" << std::endl;
    std::cout << "id author Durzal" << std::endl;
    std::cout << "option name Hash type spin default 16 min 1 max " << "128 MB" << std::endl;
    std::cout << "option name Threads type spin default 1 min 1 max " << "128 MB" << std::endl;
    std::cout << "option name OwnBook type check default false" << std::endl;
    std::cout << "option name BookPath type string" << std::endl;
    std::cout << "option name SyzygyPath type string default" << std::endl;

    std::cout << "uciok" << std::endl;
}

void uci::moves(std::string moves) {
    // does the move
    piece Piece;


    // converts the chess terms into row-col terms
    row fromCol = Board.conversion[moves[0]];
    col fromRow =  8 - (moves[1] - '0');

    row toCol = Board.conversion[moves[2]];
    col toRow = 8- (moves[3] - '0');

    // finds the piece
    Piece = Board.boardArr[fromRow][fromCol];

    Piece.nextRow = toRow;
    Piece.nextCol = toCol;

    Piece.curRow = fromRow;
    Piece.curCol = fromCol;

    // checks if its an en passant
    if (Board.boardArr[toRow][toCol].type == NONE && Piece.type == PAWN){
        // depending on color you have to +/- 1 to row
        if (Piece.color == black && Board.boardArr[toRow-1][toCol].type == PAWN && Board.boardArr[toRow-1][toCol].color == white){
            Piece.capRow = toRow-1;
            Piece.capCol = toCol;
        }else if (Piece.color == white && Board.boardArr[toRow+1][toCol].type == PAWN && Board.boardArr[toRow+1][toCol].color == black){
            Piece.capRow = toRow+1;
            Piece.capCol = toCol;
        }
    }

    // checks for castling
    if (Piece.type == KING && Piece.curCol == 4){
        if (Piece.nextCol == 2){
            // king side castle
            if (Piece.color == white) Piece.Castle = whiteCastleLeft;
            else Piece.Castle = blackCastleLeft;

        }else if (Piece.nextCol == 6){
            // queen side castle
            if (Piece.color == white) Piece.Castle = whiteCastleRight;
            else Piece.Castle = blackCastleRight;
        }
    }

    // checks for promotion
    if (moves.size() == 5){
        switch(moves[4]){
            case 'q': Piece.promotion = QUEEN; break;
            case 'r': Piece.promotion = ROOK; break;
            case 'b': Piece.promotion = BISHOP; break;
            case 'n': Piece.promotion = HORSE; break;
        }
    }

    Board.move(Piece);
}


