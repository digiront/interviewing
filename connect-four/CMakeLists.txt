project(connect-four)
cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)

add_executable(ConnectFour
        src/main.cpp src/Board.h
        src/Board.cpp
        src/Constants.h
        src/Game.cpp
        src/Game.h
        src/Player.h
        src/Player.cpp
        src/RandomPlayer.h
        src/RandomPlayer.cpp
        src/HumanPlayer.cpp
        src/HumanPlayer.h)
