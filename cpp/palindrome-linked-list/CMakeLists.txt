cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)
project(palindrome_linked_list)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(palindrome_linked_list ${SOURCE_FILES})