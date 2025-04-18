/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Nibbler
*/

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "nibbler.hpp"

arcade::Nibbler::Nibbler() : 
    _direction(Direction::RIGHT),
    _pendingDirection(Direction::RIGHT),
    _gameOver(false),
    _gameWon(false),
    _score(0),
    _highScore(0),
    _speed(200),
    _lastUpdateTime(std::chrono::steady_clock::now()),
    _foodCount(20),
    _useAlternateMap(false),
    _timeRemaining(30.0f),
    _lastTimeUpdate(std::chrono::steady_clock::now())
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    loadMap();
    loadHighScore();
    int startX = _width / 2;
    int startY = _height / 2;
    while (isWall(startX, startY)) {
        startX = std::rand() % (_width - 4) + 2;
        startY = std::rand() % (_height - 4) + 2;
    }
    
    _nibbler.push_back({startX, startY});
    _nibbler.push_back({startX - 1, startY});
    _nibbler.push_back({startX - 2, startY});
    _nibbler.push_back({startX - 3, startY});
    _nibbler.push_back({startX - 4, startY});
    _nibbler.push_back({startX - 5, startY});
    
    spawnFood();
}

arcade::Nibbler::~Nibbler() {}

void arcade::Nibbler::loadHighScore()
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

void arcade::Nibbler::saveHighScore()
{
    std::string path = getHighScoreFilePath();
    std::ofstream file(path);
    
    if (file.is_open()) {
        file << _highScore;
        file.close();
    }
}

std::string arcade::Nibbler::getHighScoreFilePath() const
{
    std::vector<std::string> possiblePaths = {
        "nibbler_highscore.txt",
        "lib/Games/nibbler/nibbler_highscore.txt",
        "assets/nibbler_highscore.txt"
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

void arcade::Nibbler::loadMap()
{
    std::vector<std::string> possiblePaths;

    if (_useAlternateMap) {
        possiblePaths = {
            "map2.txt",
            "maps/map2.txt",
            "lib/Games/nibbler/map2.txt",
            "maps/nibbler_map2.txt"
        };
    } else {
        possiblePaths = {
            "map.txt",
            "maps/map.txt",
            "lib/Games/nibbler/map.txt",
            "maps/nibbler_map.txt"
        };
    }
    
    std::ifstream mapFile;
    std::string line;
    _map.clear();
    bool fileLoaded = false;
    
    for (const auto& path : possiblePaths) {
        mapFile.open(path);
        if (mapFile.is_open()) {
            std::cout << "Loading map from: " << path << std::endl;
            while (getline(mapFile, line)) {
                std::vector<char> row;
                for (char c : line) {
                    row.push_back(c);
                }
                _map.push_back(row);
            }
            mapFile.close();
            fileLoaded = true;
            break;
        }
    }
    
    if (!fileLoaded) {
        std::cout << "No map file found, using default map" << std::endl;
        _map = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '#', '#', ' ', ' ', '#', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
        };
    }
    
    _width = _map[0].size();
    _height = _map.size();
}

bool arcade::Nibbler::isWall(int x, int y) const
{
    if (y < 0 || y >= static_cast<int>(_map.size()) || 
        x < 0 || x >= static_cast<int>(_map[y].size())) {
        return true;
    }
    return _map[y][x] == '#';
}

void arcade::Nibbler::setKey(enum KeyBind key)
{
    switch (key) {
        case KeyBind::UP_KEY:
            if (_direction != Direction::DOWN)
                _pendingDirection = Direction::UP;
            break;
        case KeyBind::DOWN_KEY:
            if (_direction != Direction::UP)
                _pendingDirection = Direction::DOWN;
            break;
        case KeyBind::LEFT_KEY:
            if (_direction != Direction::RIGHT)
                _pendingDirection = Direction::LEFT;
            break;
        case KeyBind::RIGHT_KEY:
            if (_direction != Direction::LEFT)
                _pendingDirection = Direction::RIGHT;
            break;
        case KeyBind::SPACE:
            resetGame();
            break;
        default:
            break;
    }
}

void arcade::Nibbler::update()
{
    if (_gameOver) {
        if (_score > _highScore) {
            _highScore = _score;
            saveHighScore();
        }
        return;
    }

    if (_gameWon) {
        if (_score > _highScore) {
            _highScore = _score;
            saveHighScore();
        }
        
        static auto winTime = std::chrono::steady_clock::now();
        static bool resetWinTime = true;
        if (resetWinTime) {
            winTime = std::chrono::steady_clock::now();
            resetWinTime = false;
        }
        
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - winTime).count() > 2) {
            resetWinTime = true;
            resetGame();
        }
        return;
    }
    
    auto currentTime = std::chrono::steady_clock::now();
    float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        currentTime - _lastTimeUpdate).count() / 1000.0f;
    _timeRemaining -= deltaTime;
    _lastTimeUpdate = currentTime;
    if (_timeRemaining <= 0) {
        _timeRemaining = 0;
        _gameOver = true;
        return;
    }
    if (_pendingDirection != _direction) {
        std::pair<int, int> head = _nibbler.front();
        std::pair<int, int> newHead = head;
        
        switch (_pendingDirection) {
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
        
        if (!isWall(newHead.first, newHead.second)) {
            _direction = _pendingDirection;
        }
    }
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        currentTime - _lastUpdateTime).count();
    
    if (elapsedTime > _speed) {
        moveNibbler();
        checkCollisions();
        _lastUpdateTime = currentTime;
    }
}

void arcade::Nibbler::moveNibbler()
{
    std::pair<int, int> newHead = _nibbler.front();
    
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
    if (isWall(newHead.first, newHead.second)) {
        return;
    }
    _nibbler.insert(_nibbler.begin(), newHead);
    checkFoodCollision();
    if (_foods.size() == 0) {
        _gameWon = true;
        return;
    }
}

void arcade::Nibbler::checkFoodCollision()
{
    auto head = _nibbler.front();
    bool foodEaten = false;

    for (auto it = _foods.begin(); it != _foods.end(); ) {
        if (head.first == it->first && head.second == it->second) {
            _score += 10;
            _timeRemaining += 1.0f;
            if (_speed > 50)
                _speed -= 5;
            it = _foods.erase(it);
            foodEaten = true;
            break;
        } else {
            ++it;
        }
    }
    if (!foodEaten) {
        _nibbler.pop_back();
    }
}

void arcade::Nibbler::checkCollisions()
{
    auto head = _nibbler.front();

    for (size_t i = 1; i < _nibbler.size(); i++) {
        if (head.first == _nibbler[i].first && head.second == _nibbler[i].second) {
            _gameOver = true;
            return;
        }
    }
}

void arcade::Nibbler::spawnFood()
{
    _foods.clear();
    
    for (int i = 0; i < _foodCount; i++) {
        std::pair<int, int> newFood;
        bool validPosition = false;
        
        while (!validPosition) {
            newFood.first = std::rand() % (_width - 2) + 1;
            newFood.second = std::rand() % (_height - 2) + 1;
            validPosition = true;
            
            if (isWall(newFood.first, newFood.second)) {
                validPosition = false;
                continue;
            }
            for (const auto& segment : _nibbler) {
                if (newFood.first == segment.first && newFood.second == segment.second) {
                    validPosition = false;
                    break;
                }
            }
            for (const auto& food : _foods) {
                if (newFood.first == food.first && newFood.second == food.second) {
                    validPosition = false;
                    break;
                }
            }
        }
        _foods.push_back(newFood);
    }
}

void arcade::Nibbler::resetGame()
{
    int previousScore = 0;
    if (_gameOver || _gameWon) {
        if (_score > _highScore) {
            _highScore = _score;
            saveHighScore();
        }
    }
    
    if (_gameWon) {
        previousScore = _score;
        _useAlternateMap = !_useAlternateMap;
        loadMap();
    }
    
    _nibbler.clear();
    int startX = _width / 2;
    int startY = _height / 2;
    while (isWall(startX, startY)) {
        startX = std::rand() % (_width - 4) + 2;
        startY = std::rand() % (_height - 4) + 2;
    }
    
    _nibbler.push_back({startX, startY});
    _nibbler.push_back({startX - 1, startY});
    _nibbler.push_back({startX - 2, startY});
    _nibbler.push_back({startX - 3, startY});
    _nibbler.push_back({startX - 4, startY});
    _nibbler.push_back({startX - 5, startY});
    
    _direction = Direction::RIGHT;
    _pendingDirection = Direction::RIGHT;
    _gameOver = false;
    _gameWon = false;
    _speed = 200;
    _timeRemaining = 20.0f;
    _lastTimeUpdate = std::chrono::steady_clock::now();
    if (previousScore > 0) {
        _score = previousScore;
    } else {
        _score = 0;
    }
    spawnFood();
}

std::string arcade::Nibbler::getActGame()
{
    if (_gameOver)
        return "GAME OVER";
    if (_gameWon)
        return "YOU WIN!";
    return "NIBBLER";
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::Nibbler::getDisplay(enum TGraphics lib)
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> entities;
    update();

    std::stringstream timeStream;
    timeStream << std::fixed << std::setprecision(1) << _timeRemaining;
    std::string timeStr = "Time: " + timeStream.str();
    std::string highScoreStr = "High Score: " + std::to_string(_highScore);
    const int cellSize = 20;
    
    if (lib != TGraphics::NCURSES) {
        entities.push_back({"assets/sprites/border.png", {{50, 50}, {_width * cellSize, _height * cellSize}}});
        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                if (_map[y][x] == '#') {
                    entities.push_back({"assets/sprites/border_til.png", {{50 + x * cellSize, 50 + y * cellSize}, {cellSize, cellSize}}});
                }
            }
        }
        for (const auto& food : _foods) {
            entities.push_back({"assets/sprites/pomme.png", {{50 + food.first * cellSize, 50 + food.second * cellSize}, {cellSize, cellSize}}});
        }
        for (size_t i = 0; i < _nibbler.size(); i++) {
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
            
            entities.push_back({segment, {{50 + _nibbler[i].first * cellSize, 50 + _nibbler[i].second * cellSize}, {cellSize, cellSize}}});
        }
        
        entities.push_back({"Score: " + std::to_string(_score), {{20, 20}, {0, 0}}});
        entities.push_back({highScoreStr, {{20, 40}, {0, 0}}});
        entities.push_back({timeStr, {{20, 60}, {0, 0}}});
        
        if (_gameOver) {
            entities.push_back({"GAME OVER - Continue? Press SPACE", {{180, 280}, {0, 0}}});
        }
        if (_gameWon) {
            entities.push_back({"YOU WIN!", {{180, 280}, {0, 0}}});
        }
    } else {
        entities.push_back({"CLEAR_SCREEN", {{0, 0}, {0, 0}}});
        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                if (_map[y][x] == '#') {
                    entities.push_back({"COLOR:BLUE:#", {{y, x}, {0, 0}}});
                }
            }
        }
        
        for (const auto& food : _foods) {
            entities.push_back({"COLOR:YELLOW:@", {{food.second, food.first}, {0, 0}}});
        }
        
        for (size_t i = 0; i < _nibbler.size(); i++) {
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
            entities.push_back({segment, {{_nibbler[i].second, _nibbler[i].first}, {0, 0}}});
        }
        
        entities.push_back({"Score: " + std::to_string(_score), {{_height + 1, 0}, {0, 0}}});
        entities.push_back({highScoreStr, {{_height + 1, 40}, {0, 0}}});
        entities.push_back({timeStr, {{_height + 1, 20}, {0, 0}}});
        
        if (_gameOver) {
            entities.push_back({"GAME OVER - Press SPACE to restart", {{_height + 2, 0}, {0, 0}}});
        }
        if (_gameWon) {
            entities.push_back({"YOU WIN! - Press SPACE to restart", {{_height + 2, 0}, {0, 0}}});
        }
    }
    
    return entities;
}

std::string arcade::Nibbler::getSound(enum TGraphics lib)
{
    (void)lib;
    return "";
}

int arcade::Nibbler::getScore()
{
    return _score;
}

extern "C" arcade::IGames *entryPoint() {
    return new arcade::Nibbler();
}