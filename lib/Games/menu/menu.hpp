/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "IGames.hpp"

namespace arcade {
    class Menu : public IGames {
        public:
            Menu();
            Menu(const std::vector<std::string> &gameNames);
            ~Menu() override;

            void setKey(enum KeyBind key) override;
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> getDisplay(enum TGraphics lib) override;
            std::string getSound(enum TGraphics lib) override;
            void resetGame() override;
            std::string getActGame() override;
            int getScore() override;
            bool isGameSelected() const {
                return _gameSelected;
            }
            void resetGameSelected() {
                _gameSelected = false;
            } 
            size_t getSelectedGameIndex() const {
                return _selectedGame;
            }

        private:
            size_t _selectedGame;
            bool _gameSelected = false;
            std::vector<std::string> _gameNames;
    };
}

extern "C" arcade::IGames *entryPoint() {
    return new arcade::Menu();
}

#endif