cmake_minimum_required(VERSION 3.24)
project(Matrix_lab_5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Matrix_lab_5
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Matrix.cpp
        Matrix.h
        ShortTest.cpp
        ShortTest.h)
