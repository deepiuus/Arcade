##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists.txt
##

cmake_minimum_required(VERSION 3.10)
project(arcade VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fno-gnu-unique")
endif()

## ----------------- Arcade ----------------- ##

add_executable(arcade
    src/main.cpp
    src/LibraryManager.cpp
    src/GameManager.cpp
)

set_target_properties(arcade PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

target_include_directories(arcade PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(arcade PRIVATE
    arcade_ncurses
    arcade_sdl2
    arcade_sfml
    arcade_menu
    arcade_nibbler
    arcade_snake
    dl
)

## ----------------- Ncurses ----------------- ##

find_package(Curses REQUIRED)

add_library(arcade_ncurses SHARED
    lib/Graphics/ncurses/ncurses.cpp
)

set_target_properties(arcade_ncurses PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

target_include_directories(arcade_ncurses PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CURSES_INCLUDE_DIR}
)

target_link_libraries(arcade_ncurses PRIVATE
    ${CURSES_LIBRARIES})

## ----------------- SDL ----------------- ##

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_library(arcade_sdl2 SHARED
    lib/Graphics/sdl/sdl.cpp
)

set_target_properties(arcade_sdl2 PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

target_include_directories(arcade_sdl2 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)

target_link_libraries(arcade_sdl2 PRIVATE
    SDL2 SDL2_image SDL2_ttf SDL2_mixer
)

## ----------------- SFML ----------------- ##

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

add_library(arcade_sfml SHARED
    lib/Graphics/sfml/sfml.cpp
)

set_target_properties(arcade_sfml PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

target_include_directories(arcade_sfml PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${SFML_INCLUDE_DIRS}
)

target_link_libraries(arcade_sfml PRIVATE
    sfml-graphics sfml-window sfml-system sfml-audio
)

## ----------------- Menu ----------------- ##

add_library(arcade_menu SHARED
    lib/Games/menu/menu.cpp
)

set_target_properties(arcade_menu PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

target_include_directories(arcade_menu PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

## ----------------- Nibbler ----------------- ##

add_library(arcade_nibbler SHARED
    lib/Games/nibbler/nibbler.cpp
)

set_target_properties(arcade_nibbler PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

target_include_directories(arcade_nibbler PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

## ----------------- Snake ----------------- ##

add_library(arcade_snake SHARED
    lib/Games/snake/snake.cpp
)

set_target_properties(arcade_snake PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

target_include_directories(arcade_snake PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
