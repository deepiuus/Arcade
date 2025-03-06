##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists.txt
##

cmake_minimum_required(VERSION 3.10)
project(arcade VERSION 1.0)

# Configuration C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options de compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# Définir le répertoire de sortie des bibliothèques
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Ajouter les sous-répertoires
add_subdirectory(lib/allegro)
add_subdirectory(lib/sdl)
add_subdirectory(lib/ncurses)
add_subdirectory(src)
