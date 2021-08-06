cmake_minimum_required(VERSION 3.20)
project(safeLogger)

set(CMAKE_CXX_STANDARD 17)

add_executable(safeLogger main.cpp logger.cpp logger.h)
