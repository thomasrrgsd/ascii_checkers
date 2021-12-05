cmake_minimum_required(VERSION 3.20)
project(checkers)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(checkers
        main.cpp
        menu.cpp
        menu.h
        piece.cpp
        piece.h
        checkerboard.cpp
        checkerboard.h
        boardgame.h
        checkers.cpp
        player.cpp
        computerplayer.cpp
        humanplayer.cpp
        moveObj.h moveObj.cpp)
