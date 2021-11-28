cmake_minimum_required(VERSION 3.5)

project(exam_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(exam_test main.cpp io.cpp io.h solve.cpp solve.h common.h)
