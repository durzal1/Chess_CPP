#include "bitBoard.h"

/**
* toggles the bit
* @param number    number to manipulate
* @param index     index of bit starting at the LST
* @return          the manipulated number
*/
inline void toggleBit(U64& number, Square index) {
    number ^= (1ULL << index);
}

/**
 * set the bit
 * @param number    number to manipulate
 * @param index     index of bit starting at the LST
 * @return          the manipulated number
 */
inline void setBit(U64& number, Square index) {
    number |= (1ULL << index);
}

/**
 * unset the bit
 * @param number    number to manipulate
 * @param index     index of bit starting at the LST
 * @return          the manipulated number
 */
inline void unsetBit(U64& number, Square index) {
    number &= ~(1ULL << index);
}

/**
 * get the bit
 * @param number    number to manipulate
 * @param index     index of bit starting at the LST
 * @return          the manipulated number
 */
inline bool getBit(U64 number, Square index) {
    return ((number >> index) & 1ULL) == 1;
}

inline U64 shiftWest(U64 b) {
    b = (b >> 1) & NOT_FILE_H_BB;
    return b;
}

inline U64 shiftEast(U64 b) {
    b = (b << 1) & NOT_FILE_A_BB;
    return b;
}

inline U64 shiftSouth(U64 b) {
    b = b >> 8;
    return b;
}

inline U64 shiftNorth(U64 b) {
    b = b << 8;
    return b;
}

inline U64 shiftNorthEast(U64 b) {
    b = (b << 9) & NOT_FILE_A_BB;
    return b;
}

inline U64 shiftSouthEast(U64 b) {
    b = (b >> 7) & NOT_FILE_A_BB;
    return b;
}

inline U64 shiftSouthWest(U64 b) {
    b = (b >> 9) & NOT_FILE_H_BB;
    return b;
}

inline U64 shiftNorthWest(U64 b) {
    b = (b << 7) & NOT_FILE_H_BB;
    return b;
}

/**
 * fill the bitboard to the north
 * @param b
 * @return
 */
inline U64 fillNorth(U64 b) {
    b |= (b << 8);
    b |= (b << 16);
    b |= (b << 32);
    return b;
}

/**
 * fill the bitboard to the south
 * @param b
 * @return
 */
inline U64 fillSouth(U64 b) {
    b |= (b >> 8);
    b |= (b >> 16);
    b |= (b >> 32);
    return b;
}

/**
 * fills all the files where a bit is set
 * @param b
 * @return
 */
inline U64 fillFile(U64 b) {
    return fillSouth(b) | fillNorth(b);
}

/**
 *
 * white attack        white attack     attack filefill with least one
 * frontspan           rearspan         square attacked by white
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 * . . . w . . . .     . . 1 w 1 . . .     . . 1 w 1 . . .
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 */
inline U64 wAttackFrontSpans(U64 b) {
    return fillNorth(shiftNorthEast(b) | shiftNorthWest(b));
}

/**
 *
 * white attack        white attack     attack filefill with least one
 * frontspan           rearspan         square attacked by white
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 * . . . w . . . .     . . 1 w 1 . . .     . . 1 w 1 . . .
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 */
inline U64 wAttackRearSpans(U64 b) {
    return fillSouth(shiftEast(b) | shiftWest(b));
}

/**
 *
 * black attack        black attack     attack filefill with least one
 * frontspan           rearspan         square attacked by black
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 * . . . b . . . .     . . 1 b 1 . . .     . . 1 b 1 . . .
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 */
inline U64 bAttackFrontSpans(U64 b) {
    return fillSouth(shiftSouthEast(b) | shiftSouthWest(b));
}

/**
 *
 * black attack        black attack     attack filefill with least one
 * frontspan           rearspan         square attacked by black
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 * . . . . . . . .     . . 1 . 1 . . .     . . 1 . 1 . . .
 * . . . b . . . .     . . 1 b 1 . . .     . . 1 b 1 . . .
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 * . . 1 . 1 . . .     . . . . . . . .     . . 1 . 1 . . .
 */
inline U64 bAttackRearSpans(U64 b) {
    return fillNorth(shiftEast(b) | shiftWest(b));
}

/**
 * front span for white pawns
 * @param wpawns
 * @return
 */
inline U64 wFrontSpans(U64 wpawns) {
    return shiftNorth(fillNorth(wpawns));
}

/**
 * front span for black pawns
 * @param bpawns
 * @return
 */
inline U64 bRearSpans(U64 bpawns) {
    return shiftNorth(fillNorth(bpawns));
}

/**
 * rear span for white pawns
 * @param wpawns
 * @return
 */
inline U64 wRearSpans(U64 wpawns) {
    return shiftSouth(fillSouth(wpawns));
}

/**
 * rear span for black pawns
 * @param bpawns
 * @return
 */
inline U64 bFrontSpans(U64 bpawns) {
    return shiftSouth(fillSouth(bpawns));
}

/**
 * computes all white passed pawns
 * @param wpawns
 * @param bpawns
 * @return
 */
inline U64 wPassedPawns(U64 wpawns, U64 bpawns) {
    U64 allFrontSpans = bFrontSpans(bpawns);
    allFrontSpans |= shiftEast(allFrontSpans) | shiftWest(allFrontSpans);
    return wpawns & ~allFrontSpans;
}

/**
 * computes all black passed pawns
 * @param bpawns
 * @param wpawns
 * @return
 */
inline U64 bPassedPawns(U64 bpawns, U64 wpawns) {
    U64 allFrontSpans = wFrontSpans(wpawns);
    allFrontSpans |= shiftEast(allFrontSpans) | shiftWest(allFrontSpans);
    return bpawns & ~allFrontSpans;
}

/**
 * isolates the lsb in the given number and returns the result.
 * @param number
 * @return
 */
inline U64 lsbIsolation(U64 number) {
    return number & -number;
}

/**
 * resets the lsb in the given number and returns the result.
 * @param number
 * @return
 */
inline U64 lsbReset(U64 number) {
    return number & (number - 1);
}
U64 bb::generateSlidingAttacks(Square sq, Direction direction, U64 occ) {
    U64 res {0};

    static const U64 topBottom = RANK_1_BB | RANK_8_BB;
    static const U64 leftRight = FILE_A_BB | FILE_H_BB;

    if ((1ULL << sq) & RANK_1_BB && direction < -2) {
        return res;
    }
    if ((1ULL << sq) & RANK_8_BB && direction > 2) {
        return res;
    }
    if ((1ULL << sq) & FILE_A_BB && (direction == WEST || direction == SOUTH_WEST || direction == NORTH_WEST)) {
        return res;
    }
    if ((1ULL << sq) & FILE_H_BB && (direction == EAST || direction == SOUTH_EAST || direction == NORTH_EAST)) {
        return res;
    }

    while (true) {
        sq += direction;

        U64 currentSq = (U64) 1 << sq;

        res |= currentSq;

        if (occ & currentSq) {
            return res;
        }
        if (abs(direction) == 8) {
            if (currentSq & topBottom) {
                return res;
            }
        } else if (abs(direction) == 1) {
            if (currentSq & leftRight) {
                return res;
            }
        } else {
            if (currentSq & CIRCLE_A_BB) {
                return res;
            }
        }
    }
}
U64 bb::generateRookAttack(Square sq, U64 occupied) {
    return generateSlidingAttacks(sq, NORTH, occupied) | generateSlidingAttacks(sq, EAST, occupied)
    | generateSlidingAttacks(sq, WEST, occupied) | generateSlidingAttacks(sq, SOUTH, occupied);
}

U64 bb::generateBishopAttack(Square sq, U64 occupied) {
    return generateSlidingAttacks(sq, NORTH_WEST, occupied) | generateSlidingAttacks(sq, NORTH_EAST, occupied)
    | generateSlidingAttacks(sq, SOUTH_WEST, occupied) | generateSlidingAttacks(sq, SOUTH_EAST, occupied);
}

/**
 * prints the given bitboard as a bitmap to the standard output stream
 * @param bb
 */
void  bb::printBitmap(U64 bb) {
    for (int i = 7; i >= 0; i--) {
        for (int n = 0; n < 8; n++) {
            if ((bb >> (i * 8 + n)) & (U64) 1) {
                std::cout << "1";
            } else {
                std::cout << "0";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bitboard::bitboard(){
    for (int i = 0; i < 8; i++){
        bit_boards[i] = 0ULL;
    }
};
