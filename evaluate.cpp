//
// Created by zacky on 9/3/2021.
//

#include "evaluate.h"

evaluate::evaluate() = default;


int evaluate::evaluateFunc(const board &b, Color color, int val) {
    auto arr = b.boardArr;

    // sets mg or eg (middle game and end game)
    bool mg = false;
    if (val <= 300) mg = true;

    // for debugging
    std::vector<int> vals;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            // makes sure there is a piece on it
            if (arr[i][j].type != NONE){
                // add/subtract from val depending on position
                if (arr[i][j].color == color){
                    int pos = i*8 + j;
                    if (arr[i][j].color == black) pos = (7-i) * 8 + j;

                    // NOTE for black you decrease the val since black is trying to minimize
                    switch (arr[i][j].type) {
                        // if the pieces are black it will use a different table
                        case KING:
                            if (mg){
                                if (color == white) val += mg_king_table[pos];
                                else val -= mg_king_table[pos];

                                vals.push_back(mg_king_table[pos]);
                            }else{
                                if (color == white)  val += eg_king_table[pos];
                                else val -= eg_king_table[pos];
                            }
                            break;

                        case QUEEN:
                            if (mg){
                                if (color == white) val += mg_queen_table[pos];
                                else val -= mg_queen_table[pos];

                                vals.push_back(mg_queen_table[pos]);
                            }else{
                                if (color == white) val += eg_queen_table[pos];
                                else val -= eg_queen_table[pos];
                            }
                            break;

                        case ROOK:
                            if (mg){
                                if (color == white) val += mg_rook_table[pos];
                                else val -= mg_rook_table[pos];

                                vals.push_back(mg_rook_table[pos]);
                            }else{
                                if (color == white) val += eg_rook_table[pos];
                                else val -= eg_rook_table[pos];
                            }
                            break;

                        case BISHOP:
                            if (mg){
                                if (color == white) val += mg_bishop_table[pos];
                                else val -= mg_bishop_table[pos];

                                vals.push_back(mg_bishop_table[pos]);

                            }else{
                                if (color == white) val += eg_bishop_table[pos];
                                else val -= eg_bishop_table[pos];
                            }
                            break;

                        case HORSE:
                            if (mg){
                                if (color == white) val += mg_knight_table[pos];
                                else val -= mg_knight_table[pos];

                                vals.push_back(mg_knight_table[pos]);
                            }else{
                                if (color == white) val += eg_knight_table[pos];
                                else val -= eg_knight_table[pos];

                            }
                            break;

                        case (PAWN):
                            if (mg){
                                if (color == white) val += mg_pawn_table[pos];
                                else val -= mg_pawn_table[pos];

                                vals.push_back(mg_pawn_table[pos]);
                            }else{
                                if (color == white) val += eg_pawn_table[pos];
                                else val -= eg_pawn_table[pos];
                            }
                            break;
                    }
                }
            }
        }
    }
    return val;
}
