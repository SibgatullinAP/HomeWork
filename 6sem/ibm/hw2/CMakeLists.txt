cmake_minimum_required(VERSION 3.5)

project(MPI_Solver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MPI_Solver main.cpp matrix.cpp arguments.cpp solver.cpp)
