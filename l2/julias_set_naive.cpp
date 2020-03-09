/*
g++ julias_set_naive.cpp -o julias_set_naive -march=native -mtune=native -ftree-vectorize -msse2 -ftree-vectorizer-verbose=5 -O3 -DLOG_N=9 -DSTEP_NUM=12
 */


#include"vectorization.h"
#include<array>
#include<iostream>
#include <stdlib.h>
using std::array;

const unsigned int N = (1 << LOG_N);
const unsigned int STEPS = (1 << STEP_NUM);
using T = float;

template <typename T, unsigned int N>
using Arr = array<array<T, N>, N>;


int main() {
    Arr<T, N> x;
    Arr<T, N> y;
    double c_x = 1., c_y = 1.;
    double tmp;

    // Initialize
    for (int i = 0 ; i < N ; i++) {
        for (int j = 0; j < N; j++) {
            x[i][j] = (-1. + (2. / N) * i);
            y[j][i] = x[i][j];
        }
    }
    for (int i = 0 ; i < N ; i++) {
        for (int j = 0 ; j < N ; j++) {
            for (int k = 0 ; k < STEPS ; k++) {
                tmp = x[i][j];
                tmp *= y[i][j];
                tmp *= 2.;
                tmp += c_y;
                x[i][j] *= x[i][j];
                y[i][j] *= y[i][j];
                x[i][j] += c_x;
                y[i][j] = tmp;
            }
        }
    }
    std::cout << x[rand() % N][rand() % N] <<" " << y[rand() % N][rand() % N] << '\n';
}