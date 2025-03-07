# Créer l'exécutable principal
add_executable(arcade
    main.cpp
)

# Inclure les en-têtes
target_include_directories(arcade PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Lier avec les bibliothèques dynamiques
target_link_libraries(arcade PRIVATE
    arcade_allegro5
    arcade_sdl2
    arcade_ncurses
    dl
)
