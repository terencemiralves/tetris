cmake_minimum_required(VERSION 3.0)
project(Tetris)

add_compile_options(-Wall -Wextra -Werror -pedantic -std=c++20 -g)

set(SOURCES
    src/main.cc)

add_executable(Tetris ${SOURCES})