//
// Created by zacky on 9/2/2021.
//

#ifndef CHESS_RANDOM_H
#define CHESS_RANDOM_H
#include <random>
#include <iostream>
#include <ctime>

double randomfloat(float min, float max){
    float a = static_cast<float>(rand()) / RAND_MAX * (max - min) + min;
    return a;

}
int randomint(long long int min, long long int max){;

    static const long long int p18 = 1e18;
    static const long long int p17 = 1e17;
    static const long long int p16 = 1e16;
    static const long long int p15 = 1e15;
    static const long long int p14 = 1e14;
    static const long long int p13 = 1e13;
    static const long long int p12 = 1e12;
    static const long long int p11 = 1e11;
    static const long long int p10 = 1e10;
    static const long long int p9 = 1e9;
    static const long long int p8 = 1e8;
    static const long long int p7 = 1e7;
    static const long long int p6 = 1e6;
    static const int p5 = 1e5;
    static const int p4 = 1e4;
    static const int p3 = 1e3;
    static const int p2 = 1e2;
    static const int p1 = 1e1;

    static int digit[18];

    for (int i=18; i>=0; i--)
        digit[i] = rand() % 10;

    U64 b =  digit[18] * p18
            +digit[17] * p17
            +digit[16] * p16
            + digit[15] * p15
            + digit[14] * p14
            + digit[13] * p13
            + digit[12] * p12
            + digit[11] * p11
            + digit[10] * p10
            +digit[9] * p9
            +digit[8] * p8
            +digit[7] * p7
            +digit[6] * p6
            + digit[5] * p5
            + digit[4] * p4
            + digit[3] * p3
            + digit[2] * p2
            + digit[1] * p1
            + digit[0];

    return b;

}

#endif //CHESS_RANDOM_H
