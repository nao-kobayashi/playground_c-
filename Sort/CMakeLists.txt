cmake_minimum_required(VERSION 3.19)
project(Sort)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sort main.cpp BubbleSort.h BubbleSort.cpp SelectionSort.cpp SelectionSort.h MergeSort.cpp MergeSort.h QuickSort.cpp QuickSort.h)