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
#define COLOR_BRIGHT_MAGENTA 9
#define COLOR_ORANGE 16

namespace arcade {
    class NCursesLib : public IGraphics {
        public:
            NCursesLib();
            ~NCursesLib() override;

            void Init() override;
            enum KeyBind getKey() override;
            void Display(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities) override;
            void PlaySound(std::string sound) override;
            void Clear() override;
            void Nuke() override;

        private:
            WINDOW *window;
    };
}

extern "C" arcade::IGraphics *entryPoint() {
    return new arcade::NCursesLib();
}

#endif /* !NCURSES_LIB_HPP_ */
