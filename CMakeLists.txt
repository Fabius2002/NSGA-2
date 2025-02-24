cmake_minimum_required(VERSION 3.30)
project(NSGA_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(NSGA_2 main.cpp
        Problem.hpp
        NSGA.hpp
        Help.hpp
        NSGA.cpp
        Help.cpp)
