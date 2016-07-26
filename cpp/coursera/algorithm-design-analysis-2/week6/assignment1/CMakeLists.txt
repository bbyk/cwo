cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)
project(problem)

set(SOURCE_FILES main.cpp)
add_executable(problem ${SOURCE_FILES})

file(COPY 2satT.txt 2sat1.txt 2sat2.txt 2sat3.txt 2sat4.txt 2sat5.txt 2sat6.txt DESTINATION .)
