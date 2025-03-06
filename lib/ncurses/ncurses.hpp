/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCurses
*/

#ifndef NCURSES_LIB_HPP_
#define NCURSES_LIB_HPP_

#include <ncurses.h>
#include "IGraphics.hpp"

class NCursesLib : public IGraphics {
    public:
        NCursesLib();
        ~NCursesLib() override;

        void Init() override;
        bool isRunning() override;
        void Action() override;
        void Clear() override;
        void Display() override;
        void Nuke() override;

    private:
        WINDOW *window;
        bool running;
};

extern "C" IGraphics *createGraphics() {
    return new NCursesLib();
}

#endif /* !NCURSES_LIB_HPP_ */
