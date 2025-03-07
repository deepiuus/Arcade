# Trouver SDL2
find_package(SDL2 REQUIRED)

# Créer la bibliothèque partagée
add_library(arcade_sdl2 SHARED
    sdl.cpp
)

# Inclure les en-têtes
target_include_directories(arcade_sdl2 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
)

# Lier avec SDL2
target_link_libraries(arcade_sdl2 PRIVATE
    ${SDL2_LIBRARIES})
