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
int randomint(int min, int max){
    // sets another time to add more rng
    int b = rand()%(max-min+1)+min;
    return b;

}

#endif //CHESS_RANDOM_H
