/*
g++ julias_set_vectorized.cpp -o julias_set_vectorized -march=native -mtune=native -ftree-vectorize -msse2 -ftree-vectorizer-verbose=5 -O3 -DLOG_N=9 -DSTEP_NUM=12 -DSTEP_SIZE=4
 */


#include"vectorization.h"
#include<array>
#include<iostream>
#include <stdlib.h>

using std::array;

const unsigned int N = (1 << LOG_N);
const unsigned int STEPS = (1 << STEP_NUM);
const unsigned int STEP = STEP_SIZE;
template <typename T, unsigned int N>
using Arr = array<array<T, N>, N>;

using T = float;

int main() {
    Arr<T, N> x;
    Arr<T, N> y;
    double c_x = 0.2, c_y = 0.2;

    // Initialize
    for (int i = 0 ; i < N ; i++) {
        for (int j = 0; j < N; j++) {
            x[i][j] = (-1. + (2. / N) * i);
            y[j][i] = x[i][j];
        }
    }

    VectorizedArray<T, STEP> tmp, x_vec, y_vec;
    VectorizedArray<T, STEP> two, c_x_vec, c_y_vec;
    two = 2.;
    c_x_vec = c_x;
    c_y_vec = c_y;

    for (int i = 0 ; i < N ; i++) {
        for (int j = 0 ; j < N ; j+=STEP) {
            x_vec.load(&x[i][j]);
            y_vec.load(&y[i][j]);
            for (int k = 0 ; k < STEPS ; k++) {
                tmp = x_vec;
                tmp *= y_vec;
                tmp *= two;
                tmp += c_y;
                x_vec *= x_vec;
                y_vec *= y_vec;
                x_vec += c_x_vec;
                y_vec = tmp;
            }
            x_vec.store(&x[i][j]);
            y_vec.store(&y[i][j]);
        }
    }
    std::cout << x[rand() % N][rand() % N] <<" " << y[rand() % N][rand() % N] << '\n';
}