//
// Created by zacky on 8/16/2021.
//

#ifndef CHESS_TYPES_H
#define CHESS_TYPES_H
 #include <stdint.h>

// integer value that correlates to a direction
enum Direction{
    Up,
    Down,
    Right,
    Left,
    topLeft,
    topRight,
    bottomLeft,
    bottomRight
};
enum PieceTypes{
    NONE = -1,
    PAWN   = 0,
    HORSE = 1,
    BISHOP = 2,
    ROOK   = 3,
    QUEEN  = 4,
    KING   = 5,
    N_PIECE_TYPES = 6
};
enum Color{
    white = 0,
    black = 1
};
// when getting moves this defines what it should take
// only captures, only non-captures, everything
enum Mode{
    captures = 0,
    nonCaptures = 1,
    everything = 2
};
// settings if a move is a castle
enum castle{
    none = 0,
    whiteCastleRight = 1,
    whiteCastleLeft = 2,
    blackCastleLeft = 3,
    blackCastleRight = 4
};
// type for move ordering
enum moveOrdering{
    capture = 1,
    nonCapture = 2,
    killer = 3
};
typedef uint64_t U64;
typedef uint8_t U8;
typedef int col;
typedef int row;
typedef uint8_t index;


#endif //CHESS_TYPES_H
