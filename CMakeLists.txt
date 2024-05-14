cmake_minimum_required(VERSION 3.27)
project(extra_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(extra_3 main.cpp
        graph.h
        graph.cpp
        dictionary.cpp
        game_simulation.cpp
        automatic_simulation.cpp
        analytics.cpp)
