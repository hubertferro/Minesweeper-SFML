cmake_minimum_required(VERSION 3.26)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml@2")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(minesweeper
        main.cpp
        Board.cpp
        Tile.cpp
        WelcomeWindow.cpp
)

target_link_libraries(minesweeper sfml-graphics sfml-window sfml-system)