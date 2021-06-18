cmake_minimum_required(VERSION 3.19)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Minesweeper main.cpp Game.cpp States/State.cpp States/GameState.cpp Field.cpp States/MenuState.cpp States/MenuState.h Button.cpp Button.h)

target_link_libraries(Minesweeper sfml-graphics sfml-audio)