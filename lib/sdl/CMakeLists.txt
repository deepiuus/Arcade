# Trouver SDL2
find_package(SDL2 REQUIRED)

# Créer la bibliothèque partagée
add_library(arcadeSdl SHARED
    sdl.cpp
)

# Inclure les en-têtes
target_include_directories(arcadeSdl PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
)

# Lier avec SDL2
target_link_libraries(arcadeSdl PRIVATE
    ${SDL2_LIBRARIES})
