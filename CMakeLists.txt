cmake_minimum_required(VERSION 3.16)
project(ADAShip)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

configure_file(adaship_config.ini ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
set(SOURCES src/main.cpp
        src/Ship.cpp
        src/gameController.cpp
        src/configurationReader.cpp)

add_executable(ADAShip ${SOURCES})