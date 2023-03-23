//
// Created by zacky on 8/15/2021.
//


#include "board.h"
#include <bitset>

board::board(const std::string& fen) {
    // setup the board
    FENboard(fen);

//    bb::Square SquareConversion[64] = {
//            bb::A8,bb::B8,bb::C8,bb::D8,bb::E8,bb::F8,bb::G8,bb::H8,
//            bb::A7,bb::B7,bb::C7,bb::D7,bb::E7,bb::F7,bb::G7,bb::H7,
//            bb::A6,bb::B6,bb::C6,bb::D6,bb::E6,bb::F6,bb::G6,bb::H6,
//            bb::A5,bb::B5,bb::C5,bb::D5,bb::E5,bb::F5,bb::G5,bb::H5,
//            bb::A4,bb::B4,bb::C4,bb::D4,bb::E4,bb::F4,bb::G4,bb::H4,
//            bb::A3,bb::B3,bb::C3,bb::D3,bb::E3,bb::F3,bb::G3,bb::H3,
//            bb::A2,bb::B2,bb::C2,bb::D2,bb::E2,bb::F2,bb::G2,bb::H2,
//            bb::A1,bb::B1,bb::C1,bb::D1,bb::E1,bb::F1,bb::G1,bb::H1
//    };
//
//    bb::Square SquareConversion2[64] = {
//            bb::A1,bb::B1,bb::C1,bb::D1,bb::E1,bb::F1,bb::G1,bb::H1,
//            bb::A2,bb::B2,bb::C2,bb::D2,bb::E2,bb::F2,bb::G2,bb::H2,
//            bb::A3,bb::B3,bb::C3,bb::D3,bb::E3,bb::F3,bb::G3,bb::H3,
//            bb::A4,bb::B4,bb::C4,bb::D4,bb::E4,bb::F4,bb::G4,bb::H4,
//            bb::A5,bb::B5,bb::C5,bb::D5,bb::E5,bb::F5,bb::G5,bb::H5,
//            bb::A6,bb::B6,bb::C6,bb::D6,bb::E6,bb::F6,bb::G6,bb::H6,
//            bb::A7,bb::B7,bb::C7,bb::D7,bb::E7,bb::F7,bb::G7,bb::H7,
//            bb::A8,bb::B8,bb::C8,bb::D8,bb::E8,bb::F8,bb::G8,bb::H8
//    };
//    for (int i = 0; i < 64; i++){
//        squareConversion2[i] = SquareConversion2[i];
//        squareConversion[i] = SquareConversion[i];
//    }

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            // sets zobrist values for each square
            zobVals[i][j] = zobKeys.setup();
        }
    }

    // create the conversion map
    conversion.insert({'a',0});
    conversion.insert({'b',1});
    conversion.insert({'c',2});
    conversion.insert({'d',3});
    conversion.insert({'e',4});
    conversion.insert({'f',5});
    conversion.insert({'g',6});
    conversion.insert({'h',7});

    setBitset();
}

void board::setBitset() {
    bb::printBitmap(bitBoard.bit_boards[white]);

    // gets position of the pieces
    for (int i = 0 ; i < 64; i++){
        Square square = i;

        int typee = boardArr[i].first;
        int color_ = boardArr[i].second;

        if (typee != 0){
            bb::setBit(bitBoard.bit_boards[typee], square);
            bb::setBit(bitBoard.bit_boards[color_], square);
        }

    }


}
void board::changebb(const Move &m, bb::PieceType type, bool Do, int nextColor){
    Square from = getSquareFrom(m);
    Square to = getSquareTo(m);

    auto moveType = getMovingPiece(m);
    auto capType = getCapturedPieceType(m);

    if (type == QUIET){
        if (Do){
            bb::unsetBit(bitBoard.bit_boards[moveType],from);
            bb::setBit(bitBoard.bit_boards[moveType],to);

            bb::unsetBit(bitBoard.bit_boards[playerTurn],from);
            bb::setBit(bitBoard.bit_boards[playerTurn],to);
        }else{
            bb::setBit(bitBoard.bit_boards[moveType],from);
            bb::unsetBit(bitBoard.bit_boards[moveType],to);

            bb::setBit(bitBoard.bit_boards[playerTurn],from);
            bb::unsetBit(bitBoard.bit_boards[playerTurn],to);
        }
    }else if (type == CAPTURE){

        if (Do){

            bb::unsetBit(bitBoard.bit_boards[capType],to);
            bb::unsetBit(bitBoard.bit_boards[moveType],from);
            bb::unsetBit(bitBoard.bit_boards[nextColor],to);
            bb::unsetBit(bitBoard.bit_boards[playerTurn],from);

            bb::setBit(bitBoard.bit_boards[moveType],to);
            bb::setBit(bitBoard.bit_boards[playerTurn],to);

        }else{
            bb::setBit(bitBoard.bit_boards[capType],to);
            bb::setBit(bitBoard.bit_boards[moveType],from);
            bb::setBit(bitBoard.bit_boards[nextColor],to);
            bb::setBit(bitBoard.bit_boards[playerTurn],from);

            bb::unsetBit(bitBoard.bit_boards[moveType],to);
            bb::unsetBit(bitBoard.bit_boards[playerTurn],to);
        }
    }

}
void board::move(const Move &m) {
    Square from = getSquareFrom(m);
    Square to = getSquareTo(m);

    auto type = getType(m);

    int8_t moveType = getMovingPieceType(m);
    PieceTypes moveT = PieceTypes(moveType);
//    auto capType = getCapturedPieceType(m);

    Color nextColor;

    if (playerTurn == white){
        nextColor = black;
    }else{
        nextColor = white;
    }

    if (type == QUIET){
        changebb(m, QUIET, true, nextColor);
        boardArr[from] = {NONE, white};
        boardArr[to] = {moveT, playerTurn};
    }
//    else if (type == CAPTURE){
//        changebb(m, CAPTURE, true);
//        changebb(m, QUIET, true);
//
//    }

}
void board::undoMove(const Move &m) {
    // push moves

    Square from = getSquareFrom(m);
    Square to = getSquareTo(m);

    auto capType = getCapturedPieceType(m);

    int8_t moveType = getMovingPieceType(m);
    PieceTypes moveT = PieceTypes(moveType);

    auto type = getType(m);



    Color color;
    Color oppColor;

    if (playerTurn == white){
        color = white;
        oppColor = black;
    }else{
        color = black;
        oppColor = white;
    }

    if (type == QUIET){
        changebb(m, QUIET, false, oppColor);
        boardArr[from] = {moveT, white};
        boardArr[to] = {NONE, color};
    }
//    else if (type == CAPTURE){
//
//
//        changebb(m, QUIET, false);
//        changebb(m, CAPTURE, false);
//

//    }
}

void board::FENboard(std::string FEN) {
    // temp array to store things in then put it into the main boardarr
    std::pair<PieceTypes, Color> temp [8][8];

    // reset everything
    for (auto & i : boardArr){
        i.first = NONE;
    }
    int i = 1;
    int j = 1;

    bool Castle = true;
    bool donePlacement = false;
    bool fiftymoverule = false;
    bool enPassant = false;

    int times = 0;
    std::string currentFiftyRule;
    std::string turns;
    int II = -1;
    for (char c: FEN){
        II ++;
        // done placement
        if (c == ' '){
            donePlacement = true;
            continue;
        }
        if (donePlacement){
            // total turns and 50 move rule
            if (fiftymoverule){
                if (!currentFiftyRule.empty()){
                    if (c <= '9'){
                        currentFiftyRule.push_back(c);
                    }
                    fiftymoverule = false;
                }
                if (c <= '9'){
                    // its a number so we find out if it has a second digit then save it
                    currentFiftyRule.push_back(c);
                }
            }
            else{
                // add the number to turns
                if (c <= '9'){
                    turns.push_back(c);
                }
            }

            // we dont have to change if its white since white is default start
            if (Castle){
                if (c == 'b'){
                    playerTurn = black;
                }else if (c == 'w');
                // castling rights
                else if (c == 'Q') WhiteCastleLeft = true;
                else if (c == 'q') BlackCastleLeft = true;
                else if (c == 'k') BlackCastleRight = true;
                else if (c == 'K') WhiteCastleRight = true;
                else if (c == '-'){
                    times ++;
                    if (times == 2){
                        enPassant = true;
                        Castle = false;
                    }

                }
                else{
                    enPassant = true;
                    Castle = false;
                }
            }
            // looks for any enpassant
            if (enPassant){
                if (c == '-'){
                    enPassant = false;
                    fiftymoverule = true;
                }
                else if (c <= '9'){
                    int num =8 - ( c - '0');
                    passentMoves.emplace_back(conversion[FEN[II-1]], num);
                    enPassant = false;
                    fiftymoverule = true;
                }else{
                    int num = 8 - (FEN[II+1] - '0');
                    passentMoves.emplace_back(num,conversion[c]);
                    enPassant = false;
                    fiftymoverule = true;
                }
            }

        }
        else{
            // next row
            if (c == '/'){
                i ++;
                j = 1;
            }

            // skip some cols
            if (c < '9' && c != '/'){
                int val = c - '0';
                j += val;
            }
            else{
                // its a piece

                // determine if its white or black
                if (isupper(c)) temp[i-1][j-1].second = white;
                else temp[i-1][j-1].second = black;

                switch (toupper(c)){
                    case 'K':
                        temp[i-1][j-1].first = KING;
                        break;
                    case 'Q':
                        temp[i-1][j-1].first = QUEEN;
                        break;
                    case 'R':
                        temp[i-1][j-1].first = ROOK;
                        break;
                    case 'B':
                        temp[i-1][j-1].first = BISHOP;
                        break;
                    case 'N':
                        temp[i-1][j-1].first = HORSE;
                        break;
                    case 'P':
                        temp[i-1][j-1].first = PAWN;
                        break;
                }
                if (c != '/') j++;
            }
        }

    }
    // sets the boardarr
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            boardArr[i*8+j] = temp[7-i][j];
        }
    }
    // find how many full turns there are
    if (turns.size() == 1) fullTurns = turns[0] - '9';
    else{
        // two digit number
        fullTurns = 10 * (turns[0] - '9') + (turns[1] - '9');
    }

    // 50 turn rule
    if (currentFiftyRule.size() == 1) halfTurns = currentFiftyRule[0] - '9';
    else{
        // two digit number
        halfTurns = 10 * (currentFiftyRule[0] - '9') + (currentFiftyRule[1] - '9');
    }
}

board::board() = default;

board::board(const board &b) {
    this->WhiteCastleRight = b.WhiteCastleRight;
    this->WhiteCastleLeft = b.WhiteCastleLeft;
    this->BlackCastleLeft = b.BlackCastleLeft;
    this->BlackCastleRight = b.BlackCastleRight;
    this->fullTurns = b.fullTurns;
    this->halfTurns = b.halfTurns;
    this->inter = b.inter;

    this->playerTurn = b.playerTurn;
    this->castles = b.castles;
    this->passentMoves = b.passentMoves;
    this->castleRight = b.castleRight;
    this->castleLeft = b.castleLeft;
    this->conversion = b.conversion;
    this->zobKeys = b.zobKeys;

    for (int i = 0; i < 8; i ++){
        for (int j = 0; j < 8; j++){
            this->zobVals[i][j] = b.zobVals[i][j];
            this->boardArr[i*8+j] = b.boardArr[i*8+j];
        }
    }
    this->bitBoard = b.bitBoard;
//    this->hashMoves = b.hashMoves;
}

board &board::operator=(const board &b) {
    this->WhiteCastleRight = b.WhiteCastleRight;
    this->bitBoard = b.bitBoard;
    this->WhiteCastleLeft = b.WhiteCastleLeft;
    this->BlackCastleLeft = b.BlackCastleLeft;
    this->BlackCastleRight = b.BlackCastleRight;
    this->castleRight = b.castleRight;
    this->castleLeft = b.castleLeft;
    this->fullTurns = b.fullTurns;
    this->halfTurns = b.halfTurns;
    this->castles = b.castles;
    this->inter = b.inter;
    this->playerTurn = b.playerTurn;
    this->passentMoves = b.passentMoves;
    this->conversion = b.conversion;
    this->zobKeys = b.zobKeys;
    for (int i = 0; i < 8; i ++){
        for (int j = 0; j < 8; j++){
            this->zobVals[i][j] = b.zobVals[i][j];
            this->boardArr[i*8+j] = b.boardArr[i*8+j];
        }
    }
//    this->hashMoves = b.hashMoves;

    return *this;
}


