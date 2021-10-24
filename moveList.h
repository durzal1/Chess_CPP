//
// Created by zacky on 10/21/2021.
//

#ifndef CHESS_MOVELIST_H
#define CHESS_MOVELIST_H

#include <cstdint>
#include "bitBoard.h"
#include "types.h"
typedef uint32_t Move;
typedef uint8_t  MoveType;


enum MoveTypes{
    QUIET                    = 0,
    DOUBLED_PAWN_PUSH        = 1,
    KING_CASTLE              = 2,
    QUEEN_CASTLE             = 3,
    CAPTURE                  = 4,
    EN_PASSANT               = 5,
    KNIGHT_PROMOTION         = 8,
    BISHOP_PROMOTION         = 9,
    ROOK_PROMOTION           = 10,
    QUEEN_PROMOTION          = 11,
    KNIGHT_PROMOTION_CAPTURE = 12,
    BISHOP_PROMOTION_CAPTURE = 13,
    ROOK_PROMOTION_CAPTURE   = 14,
    QUEEN_PROMOTION_CAPTURE  = 15,
    };

enum MoveTypeMasks {
    PROMOTION_MASK = 0x8,
    CAPTURE_MASK   = 0x4,
    SPECIAL_MASK   = 0x3,
    };

enum MoveShifts{
    SHIFT_FROM           = 0,
    SHIFT_TO             = 6,
    SHIFT_TYPE           = 16,
    SHIFT_MOVING_PIECE   = 12,
    SHIFT_CAPTURED_PIECE = 20,
    SHIFT_SCORE_INFO     = 24,
    };

template<uint8_t N>
constexpr uint32_t MASK = (1 << N) - 1;


inline bb::Square    getSquareFrom          (const Move& move) { return ((move >> SHIFT_FROM) & MASK<6>); }
inline bb::Square    getSquareTo            (const Move& move) { return ((move >> SHIFT_TO) & MASK<6>); }
inline MoveType      getType                (const Move& move) { return ((move >> SHIFT_TYPE) & MASK<4>); }
inline bb::Piece     getMovingPiece         (const Move& move) { return ((move >> SHIFT_MOVING_PIECE) & MASK<4>); }
inline bb::PieceType getMovingPieceType     (const Move& move) { return ((move >> SHIFT_MOVING_PIECE) & MASK<3>);}
inline bb::Piece     getCapturedPiece       (const Move& move) { return ((move >> SHIFT_CAPTURED_PIECE) & MASK<4>); }
inline bb::PieceType getCapturedPieceType   (const Move& move) { return ((move >> SHIFT_CAPTURED_PIECE) & MASK<3>); }
inline bb::Color     getMovingPieceColor    (const Move& move) { return ((move >> SHIFT_MOVING_PIECE) & 0x8);}
inline bb::Piece     getPromotionPiece      (const Move& move){ return ((move & 0x30000) >> SHIFT_TYPE) + getMovingPiece(move) + 1; }
inline bb::Piece     getPromotionPieceType  (const Move& move){ return ((move & 0x30000) >> SHIFT_TYPE) + 1; }
inline void setSquareFrom   (Move& move, const bb::Square from) {
    move |= (from << SHIFT_FROM);
}
inline void setSquareTo     (Move& move, const bb::Square to) {
    move |= (to << SHIFT_TO);
}
inline void setType         (Move& move, const MoveType type) {
    move |= (type << SHIFT_TYPE);
}
inline void setMovingPiece  (Move& move, const bb::Piece movingPiece) {
    move |= (movingPiece << SHIFT_MOVING_PIECE);
}
inline void setCapturedPiece(Move& move, const bb::Piece capturedPiece) {
    move |= (capturedPiece << SHIFT_CAPTURED_PIECE);
}

Move genMoveCap(const bb::Square &from, const bb::Square &to, const MoveType & type, const bb::Piece &movingPiece,
                    const bb::Piece &capturedPiece);
Move genMove(const bb::Square &from, const bb::Square &to, const MoveType&type, const bb::Piece &movingPiece);

void PrintMoveBits(Move move, bool bitInfo);

struct moveList{
private:
    Move moves [256];
    int size = 0;
public:
    void add(Move move);

    int getSize() const;

    Move getMove(int ind);

    void printMoveBits();



};
#endif //CHESS_MOVELIST_H
