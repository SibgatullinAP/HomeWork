cmake_minimum_required(VERSION 3.5)

project(hw_1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hw_1 main.cpp problem_info.cpp problem_info.h io.h io.cpp tex_table.cpp tex_table.h common.h math_alg.cpp math_alg.h)
