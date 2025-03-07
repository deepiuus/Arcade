# Trouver NCurses
find_package(Curses REQUIRED)

# Créer la bibliothèque partagée
add_library(arcade_ncurses SHARED
    ncurses.cpp
)

# Inclure les en-têtes
target_include_directories(arcade_ncurses PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CURSES_INCLUDE_DIR}
)

# Lier avec NCurses
target_link_libraries(arcade_ncurses PRIVATE
    ${CURSES_LIBRARIES})
