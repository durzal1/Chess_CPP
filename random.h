//
// Created by zacky on 9/2/2021.
//

#ifndef CHESS_RANDOM_H
#define CHESS_RANDOM_H
#include <random>
#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

double randomfloat(float min, float max){
    float a = static_cast<float>(rand()) / RAND_MAX * (max - min) + min;
    return a;

}
long long randomint(long long int minn, long long int maxx){;
    srand(time(0));
    return minn + (rand() % (maxx - minn + 1));

}

#endif //CHESS_RANDOM_H
