cmake_minimum_required(VERSION 3.3)
project(2DDynamicArray)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BadBorderException.cpp BadBorderException.h)
add_executable(2DDynamicArray ${SOURCE_FILES})