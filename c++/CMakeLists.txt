cmake_minimum_required(VERSION 3.15...3.21)

find_package(nlohmann_json 3.2.0 REQUIRED)

project(KIRO2022
    VERSION 1.0
    DESCRIPTION "c++ starting code for KIRO 2022"
    LANGUAGES CXX
)

add_executable(kiro2022 main.cpp instance.cpp parsing.cpp)
