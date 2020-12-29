cmake_minimum_required(VERSION 3.5)

project(hw5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hw5 main.cpp student.cpp list2.cpp list2_node.cpp)
