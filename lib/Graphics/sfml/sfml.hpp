/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Sfml
*/

#ifndef SFML_LIB_HPP_
#define SFML_LIB_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "IGraphics.hpp"

namespace arcade {
    class SfmlLib : public IGraphics {
        public:
            SfmlLib();
            ~SfmlLib() override;

            void Init() override;
            enum KeyBind getKey() override;
            void Display(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities) override;
            void renderImage(const std::string &entity, const std::pair<std::pair<int, int>, std::pair<int, int>> &pos);
            void renderText(const std::string &entity, const std::pair<std::pair<int, int>, std::pair<int, int>> &pos);
            void PlaySound(std::string sound) override;
            void Clear() override;
            void Nuke() override;

        private:
            int width;
            int height;
            int imgW;
            int imgH;
            int txtW;
            int txtH;
            sf::RenderWindow window;
            sf::Event event;
            sf::Font font;
            sf::Texture texture;
            sf::Sprite sprite;
            sf::Text text;
            sf::SoundBuffer buffer;
            sf::Sound song;
            std::string currentSound;
    };
}

#endif /* !SFML_LIB_HPP_ */

extern "C" arcade::IGraphics *entryPoint() {
    return new arcade::SfmlLib();
}
