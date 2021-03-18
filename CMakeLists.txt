cmake_minimum_required(VERSION 3.16)
project(ADAShip)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

configure_file(adaship_config.ini ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
set(SOURCES src/main.cpp
        src/Game/Ship/Ship.cpp
        src/gameController/GC.cpp
        src/configurationReader/ConfigurationReader.cpp src/Game/Board/Board.cpp src/Game/Board/Board.h src/Game/Point/Point.cpp src/Game/Point/Point.h src/Menu.cpp src/Menu.h src/Game/Game.cpp src/Game/Game.h src/gameController/GameController.cpp src/gameController/GameController.h)

add_executable(ADAShip ${SOURCES})