cmake_minimum_required(VERSION 3.15)
project(qsort)

set(CMAKE_CXX_STANDARD 17)

add_executable(qsort src/qsort.cpp src/qsort.h src/sort.h)
add_executable(test src/test.cpp src/generator.h)