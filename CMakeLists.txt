cmake_minimum_required(VERSION 3.28)
project(Battleship_War)

set(CMAKE_CXX_STANDARD 20)

add_executable(Battleship_War WIN32 main.cpp
        Core/Player.h
        UI.h
        utils.h
        Core/Point.h)
