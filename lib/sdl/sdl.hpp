/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Sdl
*/

#ifndef SDL_LIB_HPP_
#define SDL_LIB_HPP_

#include <SDL2/SDL.h>
#include "IGraphics.hpp"

class SdlLib : public IGraphics {
    public:
        SdlLib();
        ~SdlLib() override;

        void Init() override;
        bool isRunning() override;
        void Action() override;
        void Clear() override;
        void Display() override;
        void Nuke() override;

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        bool running;
};

extern "C" IGraphics *createGraphics() {
    return new SdlLib();
}

#endif /* !SDL_LIB_HPP_ */
