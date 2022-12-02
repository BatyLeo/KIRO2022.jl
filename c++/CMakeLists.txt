cmake_minimum_required(VERSION 3.15...3.21)

project(KIRO2022
    VERSION 1.0
    DESCRIPTION "c++ starting code for KIRO 2022"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20) # C++ version

add_executable(kiro2022 main.cpp instance.cpp solution.cpp parsing.cpp eval.cpp)
