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
    arcadeAllegro
    arcadeSdl
    arcadeNcurses
    dl
)
