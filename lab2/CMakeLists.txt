cmake_minimum_required(VERSION 3.26)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2 src/main.cpp
        src/numerical_methods.cpp
        src/numerical_methods.hpp)
