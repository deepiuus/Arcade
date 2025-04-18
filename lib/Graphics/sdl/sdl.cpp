/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Sdl
*/

#include "sdl.hpp"

arcade::SdlLib::SdlLib() : w(800), h(600), window(nullptr), renderer(nullptr), font(nullptr),
    imageSurface(nullptr), imageTexture(nullptr), textSurface(nullptr), textTexture(nullptr), soundEffect(nullptr), currentSound("") {}

arcade::SdlLib::~SdlLib() {}

void arcade::SdlLib::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0 || IMG_Init(IMG_INIT_PNG) == 0) {
        throw Error("Failed to initialize libs");
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw Error("Failed to initialize audio");
    }
    window = SDL_CreateWindow("Arcade SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("assets/fonts/upheavtt.ttf", 24);
    if (!font || !renderer || !window) {
        throw Error("Failed to initialize components");
    }
}

enum arcade::KeyBind arcade::SdlLib::getKey()
{
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return KeyBind::ESC;
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_a:
                    return KeyBind::A_KEY;
                case SDLK_z:
                    return KeyBind::Z_KEY;
                case SDLK_q:
                    return KeyBind::Q_KEY;
                case SDLK_s:
                    return KeyBind::S_KEY;
                case SDLK_UP:
                    return KeyBind::UP_KEY;
                case SDLK_DOWN:
                    return KeyBind::DOWN_KEY;
                case SDLK_LEFT:
                    return KeyBind::LEFT_KEY;
                case SDLK_RIGHT:
                    return KeyBind::RIGHT_KEY;
                case SDLK_SPACE:
                    return KeyBind::SPACE;
                case SDLK_RETURN:
                    return KeyBind::ENTER;
                case SDLK_ESCAPE:
                    return KeyBind::ESC;
                default:
                    break;
            }
        }
    }
    return KeyBind::NONE;
}

void arcade::SdlLib::Display(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities)
{
    for (const auto &[entity, pos] : entities) {
        if (!entity.empty() && entity.rfind("assets/", 0) == 0) {
            size_t lastSlash = entity.find_last_of('/');
            if (lastSlash != std::string::npos)
                renderImage(entity, pos);
        } else {
            renderText(entity, pos);
        }
    }
    SDL_RenderPresent(renderer);
}

void arcade::SdlLib::renderImage(const std::string &entity, const std::pair<std::pair<int, int>, std::pair<int, int>> &pos)
{
    static std::vector<std::string> failedEntities;

    if (std::find(failedEntities.begin(), failedEntities.end(), entity) != failedEntities.end())
        return;
    imageSurface = IMG_Load(entity.c_str());
    if (!imageSurface) {
        std::cerr << "Failed to load image: " << entity << " (" << IMG_GetError() << ")" << std::endl;
        failedEntities.push_back(entity);
        return;
    }
    imgW = pos.second.first == 0 ? imageSurface->w : pos.second.first;
    imgH = pos.second.second == 0 ? imageSurface->h : pos.second.second;
    imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    if (!imageTexture) {
        std::cerr << "Failed to create texture (image): " << entity << " (" << SDL_GetError() << ")" << std::endl;
        failedEntities.push_back(entity);
        return;
    }
    imageRect = {pos.first.first, pos.first.second, imgW, imgH};
    SDL_RenderCopy(renderer, imageTexture, NULL, &imageRect);
    SDL_DestroyTexture(imageTexture);
}

void arcade::SdlLib::renderText(const std::string &entity, const std::pair<std::pair<int, int>, std::pair<int, int>> &pos)
{
    textColor = {255, 255, 255, 255};
    textSurface = TTF_RenderText_Blended(font, entity.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "Failed to render text: " << entity << " (" << TTF_GetError() << ")" << std::endl;
        return;
    }
    txtW = pos.second.first == 0 ? textSurface->w : pos.second.first;
    txtH = pos.second.second == 0 ? textSurface->h : pos.second.second;
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture) {
        std::cerr << "Failed to create texture (text): " << entity << " (" << SDL_GetError() << ")" << std::endl;
        return;
    }
    textRect = {pos.first.first, pos.first.second, txtW, txtH};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
}

void arcade::SdlLib::PlaySound(std::string sound)
{
    if (!soundEffect || currentSound != sound) {
        if (soundEffect) {
            Mix_FreeChunk(soundEffect);
        }
        soundEffect = Mix_LoadWAV(sound.c_str());
        if (!soundEffect) {
            throw Error("Failed to load sound: " + sound);
        }
        currentSound = sound;
    }
    Mix_PlayChannel(-1, soundEffect, -1);
}

void arcade::SdlLib::Clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void arcade::SdlLib::Nuke()
{
    if (soundEffect) {
        Mix_FreeChunk(soundEffect);
        soundEffect = nullptr;
    }
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (font)
        TTF_CloseFont(font);
    if (window)
        SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}
