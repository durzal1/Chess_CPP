//
// Created by zacky on 8/15/2021.
//


#include "board.h"


board::board( int width) { // SDL_Window* win, SDL_Renderer* renderer1,
//    this->win = win;
//    this->renderer = renderer1;
    this->width = width;

    // interval
    inter = width/ 8;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            boardArr[i][j].curRow = i;
            boardArr[i][j].curCol = j;

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


    /*
    for zacky
    // gets the images


    pawnB = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\pawnb.png");
    horseB  = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\horseb.png");
    queenB  = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\queenb.png");
    kingB  = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\kingb.png");
    rookB = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\rookb.png");;
    bishopB  = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\bishopb.png");

    pawnW  = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\pawnw.png");
    horseW  = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\horsew.png");
    queenW = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\queenw.png");
    kingW = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\kingw.png");
    rookW= IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\rookw.png");
    bishopW = IMG_LoadTexture(renderer, "C:\\Users\\zacky\\Desktop\\Coding\\c++\\games\\chess\\Chess_CPP\\images\\bishopw.png");
    */

    /*
    for kevin
       pawnW = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\pawnw.png");
    horseW = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\horsew.png");
    queenW = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\queenw.png");
    kingW = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\kingw.png");
    rookW = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\rookw.png");
    bishopW = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\bishopw.png");

    pawnB = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\pawnb.png");
    horseB = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\horseb.png");
    queenB = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\queenb.png");
    kingB = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\kingb.png");
    rookB = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\rookb.png");;
    bishopB = IMG_LoadTexture(renderer, "C:\\Users\\kevsk\\source\\repos\\Chess\\Chess\\Chess_CPP\\images\\bishopb.png");
    */

//
//    // adds them to the textures vector
//    textures = {pawnB, horseB, queenB, kingB, rookB, bishopB, pawnW, horseW, queenW, kingW, rookW, bishopW};


    // creates the pieces and board
    this->createPieces();

    this->createBoard();
}

// inits the pieces in their respective data classes
void board::createPieces() {

    /// black
    // top row
    piece p = piece(0,0,ROOK, black);
    boardArr[0][0] = p;
    IndClass.emplace_back(ROOK);
    PieceLoc[IndClass.size()] = {0,0};
    BoardLoc[{0,0}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][1] = piece(0,1,HORSE, black);
    IndClass.emplace_back(HORSE);
    PieceLoc[IndClass.size()] = {0,1};
    BoardLoc[{0,1}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][2] = piece(0,2,BISHOP, black);
    IndClass.emplace_back(BISHOP);
    PieceLoc[IndClass.size()] = {0,2};
    BoardLoc[{0,2}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][3] = piece(0,3,QUEEN, black);
    IndClass.emplace_back(QUEEN);
    PieceLoc[IndClass.size()] = {0,3};
    BoardLoc[{0,3}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][4] = piece(0,4,KING, black);
    IndClass.emplace_back(KING);
    PieceLoc[IndClass.size()] = {0,4};
    BoardLoc[{0,4}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][5] = piece(0,5,BISHOP, black);
    IndClass.emplace_back(BISHOP);
    PieceLoc[IndClass.size()] = {0,5};
    BoardLoc[{0,5}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][6] = piece(0,6,HORSE, black);
    IndClass.emplace_back(HORSE);
    PieceLoc[IndClass.size()] = {0,6};
    BoardLoc[{0,6}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    boardArr[0][7] = piece(0,7,ROOK, black);
    IndClass.emplace_back(ROOK);
    PieceLoc[IndClass.size()] = {0,7};
    BoardLoc[{0,7}] = IndClass.size();
    blackPieces.insert(IndClass.size());

    // pawns
    for (uint64_t i = 0; i < 8; i++){
        IndClass.emplace_back(PAWN);
        boardArr[1][i] = piece(1,i,PAWN, black);
        PieceLoc[IndClass.size()] = {1,i};
        BoardLoc[{1,i}] = IndClass.size();
        blackPieces.insert(IndClass.size());
    }

    /// white
    // bottom row
    boardArr[7][0] = piece(7,0,ROOK, white);
    IndClass.emplace_back(ROOK);
    PieceLoc[IndClass.size()] = {7,0};
    BoardLoc[{7,0}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][1] = piece(7,1,HORSE, white);
    IndClass.emplace_back(HORSE);
    PieceLoc[IndClass.size()] = {7,1};
    BoardLoc[{7,1}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][2] = piece(7,2,BISHOP, white);
    IndClass.emplace_back(BISHOP);
    PieceLoc[IndClass.size()] = {7,2};
    BoardLoc[{7,2}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][3] = piece(7,3,QUEEN, white);
    IndClass.emplace_back(QUEEN);
    PieceLoc[IndClass.size()] = {7,3};
    BoardLoc[{7,3}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][4] = piece(7,4,KING, white);
    IndClass.emplace_back(KING);
    PieceLoc[IndClass.size()] = {7,4};
    BoardLoc[{7,4}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][5] = piece(7,5,BISHOP, white);
    IndClass.emplace_back(BISHOP);
    PieceLoc[IndClass.size()] = {7,5};
    BoardLoc[{7,5}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][6] = piece(7,6,HORSE, white);
    IndClass.emplace_back(HORSE);
    PieceLoc[IndClass.size()] = {7,6} ;
    BoardLoc[{7,6}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    boardArr[7][7] = piece(7,7,ROOK, white);
    IndClass.emplace_back(ROOK);
    PieceLoc[IndClass.size()] = {7,7};
    BoardLoc[{7,7}] = IndClass.size();
    whitePieces.insert(IndClass.size());

    // pawns
    for (uint64_t i = 0; i < 8; i++){
        boardArr[6][i] = piece(6,i,PAWN, white);
        IndClass.emplace_back(PAWN);
        PieceLoc[IndClass.size()] = {6,i};
        BoardLoc[{6,i}] = IndClass.size();
        whitePieces.insert(IndClass.size());
    }

}
// create board
void board::createBoard() {
//    // set color to black
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//
//    // Clear the entire screen to black
//    SDL_RenderClear(renderer);
//
//    // iterate through each square and draw it
//    for (int row = 0; row < 8; row++){
//        for (int col = 0; col<8; col++){
//            // if the row and col is even or if the row and col is even
//            if (row % 2 == 0 && col % 2 == 0 || row % 2 == 1 && col % 2 == 1){
//                // make it light
//                SDL_SetRenderDrawColor(renderer, 232,235,239, 255);
//            }
//            else{
//                // make it dark
//                SDL_SetRenderDrawColor(renderer, 125, 135, 150, 255);
//            }
//            SDL_Rect rect{col*inter, row*inter, inter, inter};
//            SDL_RenderFillRect(renderer, &rect);
//
//            // class it will draw (if any)
//            std::string piece;
//            // if theres a piece it adds it
//            if (BoardLoc.find({ row,col }) != BoardLoc.end()) {
//                // get the index
//                int index = BoardLoc[{row,col}];
//
//                // checks what piece it is
//                piece = IndClass[index -1];
//
//                // add extra mandatory character
//                if (index > 16) piece.push_back('W');
//                else piece.push_back('B');
//            }
//
//            // something belongs in the square
//            if (!piece.empty()){
//                // creates the square that will hold the png
//                SDL_Rect pieceRect{col * inter , row* inter , inter, inter};
//
//                // gets index of the texture
//                auto it = std::find(texturesStr.begin(), texturesStr.end(), piece);
//                int index = it - texturesStr.begin();
//
//                // gets the png texture
//                SDL_Texture *texture = textures[index];
//
//                // renders it
//                SDL_RenderCopy(renderer, texture, NULL, &pieceRect);
//            }
//
//        }
//    }
//    // present to screen
//    SDL_RenderPresent(renderer);
}

piece board::move(piece &Piece) {
    // vars
    row CurRow = Piece.curRow;
    col CurCol = Piece.curCol;

    row NextRow = Piece.nextRow;
    col NextCol = Piece.nextCol;

    // if the piece already has had a promotion it will not be getting demoted to pawn in these iterations
    // therefore we will remove its promotion status and just say they're a regular queen to remove confusion
    if (Piece.promotion != NONE && Piece.type != PAWN){
        Piece.promotion = NONE;
    }

    // if its a pawn promotion
    if (Piece.promotion != NONE){
        Piece.type = Piece.promotion;
    }

    // checks to see if the king/rook moved
    // if they did it will remove their right to castle

    if (Piece.type == KING && CurCol == 4){
        // makes sure it actually did a change and it wasnt already false
        if ( (Piece.color == white && WhiteCastleRight )|| (Piece.color == black && BlackCastleRight )){
            if (Piece.color == white){
                WhiteCastleRight = false;
            }else{
                BlackCastleRight = false;
            }
            Piece.rightCastleChanged = true;
        }
        if ( (Piece.color == white && WhiteCastleLeft )|| (Piece.color == black && BlackCastleLeft)){
            if (Piece.color == white){
                WhiteCastleLeft = false;
            }else{
                BlackCastleLeft = false;
            }
            Piece.leftCastleChanged = true;
        }

    }
    else if (Piece.type == ROOK){
        if (Piece.color == white){
            if (WhiteCastleLeft && Piece.curRow == 7 && Piece.curCol == 0){
                WhiteCastleLeft = false;
                Piece.leftCastleChanged = true;
            }
            else if (WhiteCastleRight && Piece.curRow == 7 && Piece.curCol == 7){
                WhiteCastleRight = false;
                Piece.rightCastleChanged = true;
            }
        }else{
            if (BlackCastleLeft && Piece.curRow == 0 && Piece.curCol == 0){
                BlackCastleLeft = false;
                Piece.leftCastleChanged = true;
            }
            else if (BlackCastleRight && Piece.curRow == 0 && Piece.curCol == 7){
                BlackCastleRight = false;
                Piece.rightCastleChanged = true;
            }
        }
    }

    // looks to see if a rook got captured
    // if it did it will remove its side's right to castle
    if (Piece.captured){
        if (Piece.color == white){
            if (Piece.nextRow == 0 && Piece.nextCol == 4){
                // removes both sides' rights
                if (BlackCastleLeft){
                    Piece.oppositeLeftCastle = true;
                    BlackCastleLeft = false;
                }
                if (BlackCastleRight){
                    Piece.oppositeRightCastle = true;
                    BlackCastleRight = false;
                }

            }else if (Piece.nextRow == 0 && Piece.nextCol == 0){
                if (BlackCastleLeft){
                    Piece.oppositeLeftCastle = true;
                    BlackCastleLeft = false;
                }
            }
            else if (Piece.nextRow == 0 && Piece.nextCol == 7){
                if (BlackCastleRight){
                    Piece.oppositeRightCastle = true;
                    BlackCastleRight = false;
                }
            }

        }else{
            if (Piece.nextRow == 7 && Piece.nextCol == 4){
                // removes both sides' rights
                if (WhiteCastleLeft){
                    Piece.oppositeLeftCastle = true;
                    WhiteCastleLeft = false;
                }
                if (WhiteCastleRight){
                    Piece.oppositeRightCastle = true;
                    WhiteCastleRight = false;
                }
            }else if (Piece.nextRow == 7 && Piece.nextCol == 0){
                if (WhiteCastleLeft){
                    Piece.oppositeLeftCastle = true;
                    WhiteCastleLeft = false;
                }
            }
            else if (Piece.nextRow == 7 && Piece.nextCol == 7){
                if (WhiteCastleRight){
                    Piece.oppositeRightCastle = true;
                    WhiteCastleRight = false;
                }
            }
        }
    }
    if (Piece.Castle != none){

        // does a castle
        if (Piece.Castle == whiteCastleLeft){
            // removing pieces
            boardArr[7][0] = piece();
            boardArr[7][4] = piece();

            // adding
            boardArr[7][2] = piece(7,2,KING, white);
            boardArr[7][3] = piece(7,3,ROOK, white);

            if (WhiteCastleRight){
                WhiteCastleRight = false;
                Piece.rightCastleChanged = true;
            }
            if (WhiteCastleLeft){
                WhiteCastleLeft = false;
                Piece.leftCastleChanged = true;
            }

        }
        else if (Piece.Castle == whiteCastleRight){
            // removing pieces
            boardArr[7][7] = piece();
            boardArr[7][4] = piece();

            // adding
            boardArr[7][6] = piece(7,6,KING, white);
            boardArr[7][5] = piece(7,5,ROOK, white);

            if (WhiteCastleRight){
                WhiteCastleRight = false;
                Piece.rightCastleChanged = true;
            }
            if (WhiteCastleLeft){
                WhiteCastleLeft = false;
                Piece.leftCastleChanged = true;
            }

        }else if (Piece.Castle == blackCastleRight){
            // removing pieces
            boardArr[0][7] = piece();
            boardArr[0][4] = piece();

            // adding
            boardArr[0][6] = piece(0,6,KING, black);
            boardArr[0][5] = piece(0,5,ROOK, black);

            if (BlackCastleRight){
                BlackCastleRight = false;
                Piece.rightCastleChanged = true;
            }
            if (BlackCastleLeft){
                BlackCastleLeft = false;
                Piece.leftCastleChanged = true;
            }
        }else if (Piece.Castle == blackCastleLeft){
            // removing pieces
            boardArr[0][0] = piece();
            boardArr[0][4] = piece();

            // adding
            boardArr[0][2] = piece(0,2,KING, black);
            boardArr[0][3] = piece(0,3,ROOK, black);

            if (BlackCastleRight){
                BlackCastleRight = false;
                Piece.rightCastleChanged = true;
            }
            if (BlackCastleLeft){
                BlackCastleLeft = false;
                Piece.leftCastleChanged = true;
            }

        }else{
            // something is wrong
            std::cout << "FIX CASTLE==============================================" << std::endl;
        }
        amountCastles ++;
        return piece();
    }

    piece oldPiece;
    if (Piece.capRow != -1){
        // its an en passant move
        // changes some variables
        Piece.curRow = NextRow;
        Piece.curCol = NextCol;

        Piece.oldRow = CurRow;
        Piece.oldCol = CurCol;

        oldPiece = boardArr[Piece.capRow][Piece.capCol];

        // changes the arrBoard
        boardArr[NextRow][NextCol] = Piece;

        // makes it empty
        boardArr[CurRow][CurCol] = piece();
        boardArr[Piece.capRow][Piece.capCol] = piece();

    }
    else{
        // changes some variables
        Piece.curRow = NextRow;
        Piece.curCol = NextCol;

        Piece.oldRow = CurRow;
        Piece.oldCol = CurCol;

        // saves the old piece
        oldPiece = boardArr[Piece.nextRow][Piece.nextCol];

        // changes the arrBoard
        boardArr[NextRow][NextCol] = Piece;

        // makes it empty
        boardArr[CurRow][CurCol] = piece();

    }
    // if this piece resulted in an en passant possibility we will add that to the board passantMoves
    if (Piece.colPassant != -1){
        this->passentMoves.emplace_back(Piece.rowPassant, Piece.colPassant);
    }


    return oldPiece;
}
void board::undoMove(piece &Piece, const piece& oldPiece) {
    // undos promotion
    if (Piece.promotion != NONE){
        Piece.type = PAWN;
        Piece.promotion = NONE;
    }

    // if there were any castle rights removed add them back
    if (Piece.rightCastleChanged){
        Piece.rightCastleChanged = false;
        if (Piece.color == white) WhiteCastleRight = true;
        else BlackCastleRight = true;
    }else if (Piece.oppositeRightCastle){
        Piece.oppositeRightCastle = false;
        if (Piece.color == white) BlackCastleRight = true;
        else WhiteCastleRight = true;
    }

    if (Piece.leftCastleChanged){
        Piece.leftCastleChanged = false;
        if (Piece.color == white) WhiteCastleLeft = true;
        else BlackCastleLeft = true;
    }else if (Piece.oppositeLeftCastle){
        Piece.oppositeLeftCastle = false;
        if (Piece.color == white)BlackCastleLeft = true;
        else WhiteCastleLeft = true;
    }


    // vars
    row CurRow = Piece.curRow;
    col CurCol = Piece.curCol;

    row OldRow = Piece.oldRow;
    col OldCol = Piece.oldCol;

    if (Piece.capRow != -1){
        // undos en passant
        // changes the arrBoard
        boardArr[Piece.curRow][Piece.curCol] = piece();

        // changes variables
        Piece.curRow = OldRow;
        Piece.oldCol = OldCol;

        boardArr[Piece.oldRow][Piece.oldCol] = Piece;
        boardArr[Piece.capRow][Piece.capCol] = oldPiece;

        boardArr[Piece.capRow][Piece.capCol].curCol = Piece.capCol;
        boardArr[Piece.capRow][Piece.capCol].curRow = Piece.capRow;

        // so the next move will not be an en passant move
        Piece.capRow = -1;
        Piece.nextCol = -1;


    }else if (Piece.Castle != none){
        // undos castle
        if (Piece.Castle == whiteCastleLeft){
            // removing pieces
            boardArr[7][2] = piece();
            boardArr[7][3] = piece();

            // adding
            boardArr[7][0] = piece(7,0,ROOK, white);
            boardArr[7][4] = piece(7,4,KING, white);

            WhiteCastleLeft = true;
            WhiteCastleRight = true;
        }
        else if (Piece.Castle == whiteCastleRight){
            // removing pieces
            boardArr[7][6] = piece();
            boardArr[7][5] = piece();

            // adding
            boardArr[7][7] = piece(7,7,ROOK, white);
            boardArr[7][4] = piece(7,4,KING, white);

            WhiteCastleRight = true;
            WhiteCastleLeft = true;

        }else if (Piece.Castle == blackCastleRight){
            // removing pieces
            boardArr[0][6] = piece();
            boardArr[0][5] = piece();

            // adding
            boardArr[0][7] = piece(0,7,ROOK, black);
            boardArr[0][4] = piece(0,4,KING, black);

            BlackCastleLeft = true;
            BlackCastleRight = true;

        }else if (Piece.Castle == blackCastleLeft){
            // removing pieces
            boardArr[0][2] = piece();
            boardArr[0][3] = piece();

            // adding
            boardArr[0][0] = piece(0,0,ROOK, black);
            boardArr[0][4] = piece(0,4,KING, black);

            BlackCastleLeft = true;
            BlackCastleRight = true;
        }
    }
    else{
        // resets the arrBoard
        boardArr[CurRow][CurCol] = oldPiece;

        // changes variables
        Piece.curRow = OldRow;
        Piece.curCol = OldCol;

        Piece.nextRow = -999;
        Piece.nextCol = -999;

        boardArr[Piece.oldRow][Piece.oldCol] = Piece;

    }

    // if this piece resulted in an en passant possibility we will remove it so it does not get used again
    if (Piece.colPassant != -1){
        this->passentMoves.clear();

        Piece.rowPassant = -1;
        Piece.colPassant = -1;
    }

}
void board::print() {
    std::cout << "" << std::endl;
    for (auto & I : boardArr){
        std::cout << "+---+---+---+---+---+---+---+---+" << std::endl;
        for (int j = 0; j < 8; j++){
            std::cout << '|' << " ";
            if (I[j].type != NONE){
                switch (I[j].type){
                    case PAWN:
                        if (I[j].color == black){
                            std::cout << 'p';
                        }else{
                            std::cout << 'P';
                        }
                        break;
                    case KING:
                        if (I[j].color == black){
                            std::cout << 'k';
                        }else{
                            std::cout << 'K';
                        }
                        break;
                    case QUEEN:
                        if (I[j].color == black){
                            std::cout << 'q';
                        }else{
                            std::cout << 'Q';
                        }
                        break;
                    case BISHOP:
                        if (I[j].color == black){
                            std::cout << 'b';
                        }else{
                            std::cout << 'B';
                        }
                        break;
                    case HORSE:
                        if (I[j].color == black){
                            std::cout << 'n';
                        }else{
                            std::cout << 'N';
                        }
                        break;
                    case ROOK:
                        if (I[j].color == black){
                            std::cout << 'r';
                        }else{
                            std::cout << 'R';
                        }
                        break;
                }
            }else std::cout << " ";
            std::cout << " ";
            if (j == 7) std::cout << '|' << std::endl;


        }
    }
}

void board::FENboard(std::string FEN) {
    // reset everything
    for (int i = 0; i < 8; i++){
        for (int j =0; j<8; j++){
            boardArr[i][j].type = NONE;
        }
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
                if (isupper(c)) boardArr[i-1][j-1].color = white;
                else boardArr[i-1][j-1].color = black;

                switch (toupper(c)){
                    case 'K':
                        boardArr[i-1][j-1].type = KING;
                        break;
                    case 'Q':
                        boardArr[i-1][j-1].type = QUEEN;
                        break;
                    case 'R':
                        boardArr[i-1][j-1].type = ROOK;
                        break;
                    case 'B':
                        boardArr[i-1][j-1].type = BISHOP;
                        break;
                    case 'N':
                        boardArr[i-1][j-1].type = HORSE;
                        break;
                    case 'P':
                        boardArr[i-1][j-1].type = PAWN;
                        break;
                }
                if (c != '/') j++;
            }
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

board::board() {

}

board::board(const board &b) {
    this->WhiteCastleRight = b.WhiteCastleRight;
    this->WhiteCastleLeft = b.WhiteCastleLeft;
    this->BlackCastleLeft = b.BlackCastleLeft;
    this->BlackCastleRight = b.BlackCastleRight;
    this->fullTurns = b.fullTurns;
    this->halfTurns = b.halfTurns;
    this->inter = b.inter;
    for (int i = 0; i < 8; i ++){
        for (int j = 0; j < 8; j++){
            this->boardArr[i][j] = b.boardArr[i][j];
        }
    }
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
        }
    }
}

board &board::operator=(const board &b) {
    this->WhiteCastleRight = b.WhiteCastleRight;
    this->WhiteCastleLeft = b.WhiteCastleLeft;
    this->BlackCastleLeft = b.BlackCastleLeft;
    this->BlackCastleRight = b.BlackCastleRight;
    this->castleRight = b.castleRight;
    this->castleLeft = b.castleLeft;
    this->fullTurns = b.fullTurns;
    this->halfTurns = b.halfTurns;
    this->castles = b.castles;
    this->inter = b.inter;
    for (int i = 0; i < 8; i ++){
        for (int j = 0; j < 8; j++){
            this->boardArr[i][j] = b.boardArr[i][j];
        }
    }
    this->playerTurn = b.playerTurn;
    this->passentMoves = b.passentMoves;
    this->conversion = b.conversion;
    this->zobKeys = b.zobKeys;
    for (int i = 0; i < 8; i ++){
        for (int j = 0; j < 8; j++){
            this->zobVals[i][j] = b.zobVals[i][j];
        }
    }
    return *this;
}

