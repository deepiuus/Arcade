/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "IGames.hpp"
#include <vector>
#include <utility>
#include <chrono>
#include <fstream>
#include <string>

namespace arcade {
    class Snake : public IGames {
        public:
            Snake();
            ~Snake() override;

            void setKey(enum KeyBind key) override;
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> getDisplay(enum TGraphics lib) override;
            std::string getSound(enum TGraphics lib) override;
            void resetGame() override;
            std::string getActGame() override;
            int getScore() override;

        private:
            const int _width;
            const int _height;
            std::vector<std::pair<int, int>> _snake;
            enum Direction { UP, DOWN, LEFT, RIGHT } _direction;
            std::pair<int, int> _food;
            bool _gameOver;
            int _score;
            int _highScore;
            int _speed;
            std::chrono::steady_clock::time_point _lastUpdateTime;
            void update();
            void moveSnake();
            void checkCollisions();
            void spawnFood();
            void reset();
            
            void loadHighScore();
            void saveHighScore();
            std::string getHighScoreFilePath() const;
    };
}

extern "C" arcade::IGames *entryPoint();

#endif