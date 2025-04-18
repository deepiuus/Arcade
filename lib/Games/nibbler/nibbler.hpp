/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "IGames.hpp"
#include <vector>
#include <utility>
#include <chrono>
#include <string>
#include <fstream>

namespace arcade {
    class Nibbler : public IGames {
        public:
            Nibbler();
            ~Nibbler() override;

            void setKey(enum KeyBind key) override;
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> getDisplay(enum TGraphics lib) override;
            std::string getSound(enum TGraphics lib) override;
            void resetGame() override;
            std::string getActGame() override;
            int getScore() override;

        private:
            enum Direction { UP, DOWN, LEFT, RIGHT } _direction;
            Direction _pendingDirection;
            std::vector<std::vector<char>> _map;
            std::vector<std::pair<int, int>> _nibbler;
            std::vector<std::pair<int, int>> _foods;
            bool _gameOver;
            bool _gameWon;
            int _score;
            int _highScore;
            int _speed;
            std::chrono::steady_clock::time_point _lastUpdateTime;
            int _width;
            int _height;
            int _foodCount;
            bool _useAlternateMap;
            float _timeRemaining;
            std::chrono::steady_clock::time_point _lastTimeUpdate;
            
            void loadMap();
            void update();
            void moveNibbler();
            void checkCollisions();
            void spawnFood();
            bool isWall(int x, int y) const;
            void checkFoodCollision();
            void reset();
            void loadHighScore();
            void saveHighScore();
            std::string getHighScoreFilePath() const;
    };
}

extern "C" arcade::IGames *entryPoint();

#endif /* !NIBBLER_HPP_ */
