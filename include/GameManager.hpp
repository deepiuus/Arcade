/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** GameManager
*/

#ifndef GAME_MANAGER_HPP_
#define GAME_MANAGER_HPP_

#include "IGames.hpp"

namespace arcade {
    class GameManager {
        public:
            GameManager();
            ~GameManager();
            void loadGames(const std::string &gameDir);
            IGames *nextGame();
            IGames *previousGame();
            IGames *getCurrentGame() const;
            void setCurrentGame(const std::string &gameName);
            std::vector<std::string> getDisplayNames() const;
        private:
            void *_currentHandle;
            size_t _currentIndex;
            IGames *_currentGame;
            IGames *loadGame(const std::string &gamePath);
            std::vector<std::string> findGames(const std::string &gameDir);
            std::map<TGames, std::string> _assignType;
            std::map<std::string, TGames> _assignGame;
            std::map<std::string, std::string> _gamePaths;
            std::vector<std::string> _gameNames;
            std::map<std::string, std::string> _gameDisplay;
    };
}

#endif /* !GAME_MANAGER_HPP_ */
