# Trouver NCurses
find_package(Curses REQUIRED)

# Créer la bibliothèque partagée
add_library(arcadeNcurses SHARED
    ncurses.cpp
)

# Inclure les en-têtes
target_include_directories(arcadeNcurses PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CURSES_INCLUDE_DIR}
)

# Lier avec NCurses
target_link_libraries(arcadeNcurses PRIVATE
    ${CURSES_LIBRARIES})
