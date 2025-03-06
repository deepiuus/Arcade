/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCurses
*/

#include "ncurses.hpp"

NCursesLib::NCursesLib() : window(nullptr), running(false)
{
    Init();
}

NCursesLib::~NCursesLib()
{
    Nuke();
}

void NCursesLib::Init()
{
    window = initscr();
    if (!window) {
        running = false;
        return;
    }
    noecho();
    cbreak();
    keypad(window, TRUE);
    nodelay(window, TRUE);
    curs_set(0);
    start_color();
    running = true;
}

bool NCursesLib::isRunning()
{
    return running;
}

void NCursesLib::Action()
{
    int ch = getch();
    if (ch != ERR) {
        switch (ch) {
            case 27:  // ESC
            case 'q':
            case 'Q':
                running = false;
                break;
            default:
                break;
        }
    }
}

void NCursesLib::Clear()
{
    wclear(window);
}

void NCursesLib::Display()
{
    wrefresh(window);
}

void NCursesLib::Nuke()
{
    if (window) {
        delwin(window);
        endwin();
    }
}
