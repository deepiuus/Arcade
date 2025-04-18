/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IGraphics
*/

#ifndef IGRAPHICS_HPP_
#define IGRAPHICS_HPP_

#include <dlfcn.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <algorithm>
#include "Error.hpp"

namespace arcade {
    
    enum class KeyBind {
        ESC,
        A_KEY,
        Z_KEY,
        Q_KEY,
        S_KEY,
        UP_KEY,
        DOWN_KEY,
        LEFT_KEY,
        RIGHT_KEY,
        SPACE,
        ENTER,
        NONE
    };
    
    enum class TGraphics {
        NCURSES,
        SDL,
        NDK,
        AA,
        CACA,
        ALLEGRO,
        X,
        GTK,
        SFML,
        IRRLICHT,
        OPENGL,
        VULKAN,
        QT
    };

    class IGraphics {
        public:
            virtual ~IGraphics() = default;
            virtual void Init() = 0;
            virtual enum KeyBind getKey() = 0;
            virtual void Display(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities) = 0;
            virtual void PlaySound(std::string sound) = 0;
            virtual void Clear() = 0;
            virtual void Nuke() = 0;
    };
}

#endif /* !IGRAPHICS_HPP_ */
