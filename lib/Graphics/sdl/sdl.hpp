/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Sdl
*/

#ifndef SDL_LIB_HPP_
#define SDL_LIB_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "IGraphics.hpp"

namespace arcade {
    class SdlLib : public IGraphics {
        public:
            SdlLib();
            ~SdlLib() override;

            void Init() override;
            enum KeyBind getKey() override;
            void Display(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities) override;
            void renderImage(const std::string &entity, const std::pair<std::pair<int, int>, std::pair<int, int>> &pos);
            void renderText(const std::string &entity, const std::pair<std::pair<int, int>, std::pair<int, int>> &pos);
            void PlaySound(std::string sound) override;
            void Clear() override;
            void Nuke() override;

        private:
            int w;
            int h;
            int imgW;
            int imgH;
            int txtW;
            int txtH;
            std::string cleanEntity;
            SDL_Window *window;
            SDL_Renderer *renderer;
            SDL_Event event;
            TTF_Font *font;
            SDL_Surface *imageSurface;
            SDL_Texture *imageTexture;
            SDL_Rect imageRect;
            SDL_Color textColor;
            SDL_Surface *textSurface;
            SDL_Texture *textTexture;
            SDL_Rect textRect;
            Mix_Chunk *soundEffect;
            std::string currentSound;
    };
}

extern "C" arcade::IGraphics *entryPoint() {
    return new arcade::SdlLib();
}

#endif /* !SDL_LIB_HPP_ */
