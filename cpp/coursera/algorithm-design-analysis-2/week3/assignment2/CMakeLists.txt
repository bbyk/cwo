cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)
project(problem)

set(SOURCE_FILES main.cpp)
add_executable(problem ${SOURCE_FILES})

file(COPY knapsack_big.txt DESTINATION .)
