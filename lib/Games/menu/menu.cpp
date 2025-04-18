/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Menu
*/

#include "menu.hpp"

arcade::Menu::Menu() : _selectedGame(0)
{
    _gameNames.insert(_gameNames.begin(), "MENU");
}

arcade::Menu::Menu(const std::vector<std::string> &gameNames) : _selectedGame(0), _gameSelected(false), _gameNames(gameNames) {}

arcade::Menu::~Menu() {}

void arcade::Menu::setKey(enum KeyBind key)
{
    switch (key) {
        case KeyBind::UP_KEY:
            if (_selectedGame > 0)
                _selectedGame--;
            break;
        case KeyBind::DOWN_KEY:
            if (_selectedGame < _gameNames.size() - 1)
                _selectedGame++;
            break;
        case KeyBind::ENTER:
            _gameSelected = true;
            break;
        default:
            break;
    }
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::Menu::getDisplay(enum TGraphics lib)
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> entities;

    if (lib != TGraphics::NCURSES) {
        entities.push_back({"assets/sprites/menu.jpg", {{160, 100}, {474, 360}}});
        entities.push_back({"assets/sprites/arcade.png", {{150, 0}, {500, 100}}});
        entities.push_back({"MENU", {{360, 150}, {0, 0}}});
        
        for (size_t i = 0; i < _gameNames.size(); i++) {
            std::string prefix = (i == _selectedGame) ? ">> " : "   ";
            entities.push_back({prefix + _gameNames[i], {{220, 200 + static_cast<int>(i) * 40}, {0, 0}}});
        }
        entities.push_back({"Use UP/DOWN arrows to select, ENTER to confirm", {{100, 500}, {0, 0}}});
    } else {
        int startY = 2;
        int startX = 1;
        entities.push_back({"+" + std::string(20, '-') + "+", {{startY, startX}, {0, 0}}});
        entities.push_back({"|" + std::string(20, ' ') + "|", {{startY + 1, startX}, {0, 0}}});
        entities.push_back({"|        MENU" + std::string(8, ' ') + "|", {{startY + 2, startX}, {0, 0}}});
        entities.push_back({"|" + std::string(20, ' ') + "|", {{startY + 3, startX}, {0, 0}}});

        for (size_t i = 0; i < _gameNames.size(); i++) {
            std::string prefix = (i == _selectedGame) ? ">> " : "   ";
            std::string line = prefix + _gameNames[i];
            line += std::string(20 - line.size(), ' ');
            entities.push_back({"|" + line + "|", {{startY + 4 + static_cast<int>(i), startX}, {0, 0}}});
        }
        entities.push_back({"|" + std::string(20, ' ') + "|", {{startY + 4 + static_cast<int>(_gameNames.size()), startX}, {0, 0}}});
        entities.push_back({"+" + std::string(20, '-') + "+", {{startY + 5 + static_cast<int>(_gameNames.size()), startX}, {0, 0}}});
        entities.push_back({"Use UP/DOWN arrows to select, ENTER to confirm", {{startY + 7 + static_cast<int>(_gameNames.size()), startX}, {0, 0}}});
    }
    return entities;
}

std::string arcade::Menu::getSound(enum TGraphics lib)
{
    if (lib != TGraphics::NCURSES) {
        return "assets/sounds/main.wav";
    }
    return "";
}

void arcade::Menu::resetGame()
{
    return;
}

std::string arcade::Menu::getActGame()
{
    if (_selectedGame < _gameNames.size())
        return _gameNames[_selectedGame];
    return "MENU";
}

int arcade::Menu::getScore()
{
    return 0;
}