/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IGames.hpp
*/

#ifndef IGAMES_HPP_
#define IGAMES_HPP_

#include <dlfcn.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <algorithm>
#include "IGraphics.hpp"

namespace arcade {

    enum class TGames {
        MENU,
        SNAKE,
        MINESWEEPER,
        NIBBLER,
        PACMAN,
        QIX,
        CENTIPEDE,
        SOLARFOX,
        SOKOBAN,
        SPACE,
        TETRIS,
        THE_SHOW
    };

    class IGames {
        public:
            virtual ~IGames() = default;
            virtual void setKey(enum KeyBind key) = 0;
            virtual std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> getDisplay(enum TGraphics lib) = 0;
            virtual std::string getSound(enum TGraphics lib) = 0;
            virtual void resetGame() = 0;
            virtual std::string getActGame() = 0;
            virtual int getScore() = 0;
    };
}

#endif /* !IGAMES_HPP_ */
