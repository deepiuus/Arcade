/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCurses
*/

#include "ncurses.hpp"

arcade::NCursesLib::NCursesLib() : window(nullptr) {}

arcade::NCursesLib::~NCursesLib() {}

void arcade::NCursesLib::Init()
{
    if (!window) {
        window = initscr();
        if (!window)
            return;
    }
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();

    if (can_change_color()) {
        init_color(COLOR_ORANGE, 1000, 500, 0);
    }
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(9, COLOR_BRIGHT_MAGENTA, COLOR_BLACK);
    init_pair(10, COLOR_BLACK, COLOR_YELLOW);
    init_pair(8, COLOR_YELLOW, COLOR_WHITE);
    init_pair(11, COLOR_BLACK, COLOR_BLUE);
    init_pair(12, COLOR_BLACK, COLOR_RED);
    init_pair(13, COLOR_WHITE, COLOR_GREEN);
    init_pair(14, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(15, COLOR_BLACK, COLOR_CYAN);
    init_pair(16, COLOR_BLACK, COLOR_ORANGE);
}

enum arcade::KeyBind arcade::NCursesLib::getKey() {
    int key = getch();
    switch (key) {
        case KEY_UP:
            return arcade::KeyBind::UP_KEY;
        case KEY_DOWN:
            return arcade::KeyBind::DOWN_KEY;
        case KEY_LEFT:
            return arcade::KeyBind::LEFT_KEY;
        case KEY_RIGHT:
            return arcade::KeyBind::RIGHT_KEY;
        case ' ':
            return arcade::KeyBind::SPACE;
        case 27:
            return arcade::KeyBind::ESC;
        case 10:
            return arcade::KeyBind::ENTER;
        case 'a':
            return arcade::KeyBind::A_KEY;
        case 'z':
            return arcade::KeyBind::Z_KEY;
        case 'q':
            return arcade::KeyBind::Q_KEY;
        case 's':
            return arcade::KeyBind::S_KEY;
        default:
            break;
    }
    return arcade::KeyBind::NONE;
}

void arcade::NCursesLib::Display(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities)
{
    for (const auto &entity : entities) {
        if (entity.first == "CLEAR_SCREEN") {
            wclear(window);
            break;
        }
    }
    
    for (const auto &[name, pos] : entities) {
        if (name != "CLEAR_SCREEN" && pos.first.first >= 0 && pos.first.second >= 0) {
            if (name.substr(0, 6) == "COLOR:") {
                size_t firstColon = name.find(':');
                size_t secondColon = name.find(':', firstColon + 1);
                std::string color = name.substr(firstColon + 1, secondColon - firstColon - 1);
                std::string text = name.substr(secondColon + 1);
                
                int colorPair = 7;
                if (color == "RED") colorPair = 1;
                else if (color == "GREEN") colorPair = 2;
                else if (color == "YELLOW") colorPair = 3;
                else if (color == "BLUE") colorPair = 4;
                else if (color == "MAGENTA") colorPair = 5;
                else if (color == "CYAN") colorPair = 6;
                
                attron(COLOR_PAIR(colorPair));
                mvprintw(pos.first.first, pos.first.second, "%s", text.c_str());
                attroff(COLOR_PAIR(colorPair));
            } else {
                mvprintw(pos.first.first, pos.first.second, "%s", name.c_str());
            }
        }
    }
    refresh();
}

void arcade::NCursesLib::PlaySound(std::string sound)
{
    (void)sound;
}

void arcade::NCursesLib::Clear()
{
    wclear(window);
}

void arcade::NCursesLib::Nuke()
{
    if (window) {
        endwin();
        window = nullptr;
    }
}
