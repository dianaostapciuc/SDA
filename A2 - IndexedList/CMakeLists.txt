cmake_minimum_required(VERSION 3.24)
project(IndexedList_lab_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(IndexedList_lab_2
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        IndexedList.cpp
        IndexedList.h
        ListIterator.cpp
        ListIterator.h
        ShortTest.cpp
        ShortTest.h)
