# Trouver Allegro
find_package(PkgConfig REQUIRED)
pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_main-5)

# Créer la bibliothèque partagée
add_library(arcadeAllegro SHARED
    allegro.cpp
)

# Inclure les en-têtes
target_include_directories(arcadeAllegro PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${ALLEGRO5_INCLUDE_DIRS}
)

# Lier avec Allegro
target_link_libraries(arcadeAllegro PRIVATE
    ${ALLEGRO5_LIBRARIES}
)
