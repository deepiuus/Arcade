/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Sdl
*/

#include "sdl.hpp"

SdlLib::SdlLib() : window(nullptr), renderer(nullptr), running(false)
{
    Init();
}

SdlLib::~SdlLib()
{
    Nuke();
}

void SdlLib::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        running = false;
        return;
    }
    window = SDL_CreateWindow(
        "Arcade SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        running = false;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        running = false;
        return;
    }
    running = true;
}

bool SdlLib::isRunning()
{
    return running;
}

void SdlLib::Action()
{
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE
            || event.key.keysym.sym == SDLK_q)
                running = false;
        }
    }
}

void SdlLib::Clear()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void SdlLib::Display()
{
    SDL_RenderPresent(renderer);
}

void SdlLib::Nuke()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}
