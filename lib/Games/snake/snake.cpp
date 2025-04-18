/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Snake
*/

#include "snake.hpp"
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

arcade::Snake::Snake() : 
    _width(70), 
    _height(50),
    _direction(Direction::RIGHT),
    _gameOver(false),
    _score(0),
    _highScore(0),
    _speed(150),
    _lastUpdateTime(std::chrono::steady_clock::now())
{
    loadHighScore();
    _snake.push_back({_width / 2, _height / 2});
    _snake.push_back({_width / 2 - 1, _height / 2});
    _snake.push_back({_width / 2 - 2, _height / 2});
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    spawnFood();
}

arcade::Snake::~Snake() {}

void arcade::Snake::loadHighScore()
{
    std::string path = getHighScoreFilePath();
    std::ifstream file(path);
    
    if (file.is_open()) {
        file >> _highScore;
        file.close();
    } else {
        _highScore = 0;
    }
}

void arcade::Snake::saveHighScore()
{
    std::string path = getHighScoreFilePath();
    std::ofstream file(path);
    
    if (file.is_open()) {
        file << _highScore;
        file.close();
    }
}

std::string arcade::Snake::getHighScoreFilePath() const
{
    std::vector<std::string> possiblePaths = {
        "snake_highscore.txt",
        "lib/Games/snake/snake_highscore.txt",
        "assets/snake_highscore.txt"
    };
    
    for (const auto& path : possiblePaths) {
        std::ifstream test(path);
        if (test.good()) {
            test.close();
            return path;
        }
        test.close();
    }
    
    return possiblePaths[0];
}

void arcade::Snake::setKey(enum KeyBind key)
{
    switch (key) {
        case KeyBind::UP_KEY:
            if (_direction != Direction::DOWN)
                _direction = Direction::UP;
            break;
        case KeyBind::DOWN_KEY:
            if (_direction != Direction::UP)
                _direction = Direction::DOWN;
            break;
        case KeyBind::LEFT_KEY:
            if (_direction != Direction::RIGHT)
                _direction = Direction::LEFT;
            break;
        case KeyBind::RIGHT_KEY:
            if (_direction != Direction::LEFT)
                _direction = Direction::RIGHT;
            break;
        case KeyBind::SPACE:
            reset();
            break;
        default:
            break;
    }
}

void arcade::Snake::update()
{
    if (_gameOver) {
        if (_score > _highScore) {
            _highScore = _score;
            saveHighScore();
        }
        return;
    }
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        currentTime - _lastUpdateTime).count();
    if (elapsedTime > _speed) {
        moveSnake();
        checkCollisions();
        _lastUpdateTime = currentTime;
    }
}

void arcade::Snake::moveSnake()
{
    std::pair<int, int> newHead = _snake.front();   
    switch (_direction) {
        case Direction::UP:
            newHead.second--;
            break;
        case Direction::DOWN:
            newHead.second++;
            break;
        case Direction::LEFT:
            newHead.first--;
            break;
        case Direction::RIGHT:
            newHead.first++;
            break;
    }
    _snake.insert(_snake.begin(), newHead);
    if (newHead.first == _food.first && newHead.second == _food.second) {
        _score += 10;
        spawnFood();
    } else {
        _snake.pop_back();
    }
}

void arcade::Snake::checkCollisions()
{
    auto head = _snake.front();
    if (head.first < 0 || head.first >= _width || 
        head.second < 0 || head.second >= _height) {
        _gameOver = true;
        return;
    }
    for (size_t i = 1; i < _snake.size(); i++) {
        if (head.first == _snake[i].first && head.second == _snake[i].second) {
            _gameOver = true;
            return;
        }
    }
}

void arcade::Snake::spawnFood()
{
    bool validPosition = false;
    
    while (!validPosition) {
        _food.first = std::rand() % _width;
        _food.second = std::rand() % _height;
        
        validPosition = true;
        for (const auto& segment : _snake) {
            if (_food.first == segment.first && _food.second == segment.second) {
                validPosition = false;
                break;
            }
        }
    }
}

void arcade::Snake::reset()
{
    if (_gameOver) {
        if (_score > _highScore) {
            _highScore = _score;
            saveHighScore();
        }
    }
    
    _snake.clear();
    _snake.push_back({_width / 2, _height / 2});
    _snake.push_back({_width / 2 - 1, _height / 2});
    _snake.push_back({_width / 2 - 2, _height / 2});
    
    _direction = Direction::RIGHT;
    _gameOver = false;
    _score = 0;
    
    spawnFood();
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::Snake::getDisplay(enum TGraphics lib)
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> entities;
    update();

    const int cellSize = 10;
    std::string highScoreStr = "High Score: " + std::to_string(_highScore);

    if (lib != TGraphics::NCURSES) {
        entities.push_back({"assets/sprites/menu.jpg", {{160, 100}, {0, 0}}});
        entities.push_back({"assets/sprites/border.png", {{50, 50}, {_width * cellSize, _height * cellSize}}});
        entities.push_back({"Score: " + std::to_string(_score), {{20, 20}, {0, 0}}});
        entities.push_back({highScoreStr, {{20, 40}, {0, 0}}});
        if (_gameOver) {
            entities.push_back({"GAME OVER - Continue? Press SPACE", {{180, 280}, {0, 0}}});
        }
        entities.push_back({"assets/sprites/pomme.png", {{50 + _food.first * cellSize, 50 + _food.second * cellSize}, {cellSize, cellSize}}});
        for (size_t i = 0; i < _snake.size(); i++) {
            std::string segment;
            if (i == 0) {
                switch (_direction) {
                    case Direction::UP:
                        segment = "assets/sprites/snake_head_up.png";
                        break;
                    case Direction::DOWN:
                        segment = "assets/sprites/snake_head_down.png";
                        break;
                    case Direction::LEFT:
                        segment = "assets/sprites/snake_head_left.png";
                        break;
                    case Direction::RIGHT:
                        segment = "assets/sprites/snake_head_right.png";
                        break;
                }
            } else {
                segment = "assets/sprites/snake_body.png";
            }
            
            entities.push_back({segment, {{50 + _snake[i].first * cellSize, 50 + _snake[i].second * cellSize}, {cellSize, cellSize}}});
        }
    } else {
        entities.push_back({"CLEAR_SCREEN", {{0, 0}, {0, 0}}});
        for (int x = 0; x < _width + 2; x++) {
            entities.push_back({"COLOR:BLUE:-", {{0, x}, {0, 0}}});
            entities.push_back({"COLOR:BLUE:-", {{_height + 1, x}, {0, 0}}});
        }
        for (int y = 0; y < _height + 2; y++) {
            entities.push_back({"COLOR:BLUE:|", {{y, 0}, {0, 0}}});
            entities.push_back({"COLOR:BLUE:|", {{y, _width + 1}, {0, 0}}});
        }
        entities.push_back({"Score: " + std::to_string(_score), {{_height + 3, 1}, {0, 0}}});
        entities.push_back({highScoreStr, {{_height + 3, 40}, {0, 0}}});
        if (_gameOver) {
            entities.push_back({"GAME OVER - Press SPACE to restart", {{_height + 4, 1}, {0, 0}}});
        }
        entities.push_back({"COLOR:YELLOW:@", {{_food.second + 1, _food.first + 1}, {0, 0}}});
        for (size_t i = 0; i < _snake.size(); i++) {
            std::string segment;
            if (i == 0) {
                switch (_direction) {
                    case Direction::UP:
                        segment = "COLOR:RED:^";
                        break;
                    case Direction::DOWN:
                        segment = "COLOR:RED:v";
                        break;
                    case Direction::LEFT:
                        segment = "COLOR:RED:<";
                        break;
                    case Direction::RIGHT:
                        segment = "COLOR:RED:>";
                        break;
                }
            } else {
                segment = "COLOR:GREEN:o";
            }
            entities.push_back({segment, {{_snake[i].second + 1, _snake[i].first + 1}, {0, 0}}});
        }
    }
    
    return entities;
}

std::string arcade::Snake::getSound(enum TGraphics lib)
{
    (void)lib;
    return "";
}

void arcade::Snake::resetGame()
{
    reset();
}

std::string arcade::Snake::getActGame()
{
    if (_gameOver)
        return "GAME OVER";
    return "SNAKE";
}

int arcade::Snake::getScore()
{
    return _score;
}

extern "C" arcade::IGames *entryPoint() {
    return new arcade::Snake();
}