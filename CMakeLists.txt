cmake_minimum_required(VERSION 3.27)
project(SudokuSolver C)

set(CMAKE_C_STANDARD 11)

add_library(SudokuSolver SHARED sudokusolver.c)
