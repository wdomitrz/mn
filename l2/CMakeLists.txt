cmake_minimum_required(VERSION 3.15)
project(l2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(julia_set
        julias_set_naive.cpp
        vectorization.h)
