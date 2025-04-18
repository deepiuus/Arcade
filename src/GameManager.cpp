/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** GameManager
*/

#include "GameManager.hpp"

arcade::GameManager::GameManager() : _currentHandle(nullptr), _currentIndex(0), _currentGame(nullptr)
{
    _assignType[TGames::MENU] = "arcade_menu.so";
    _assignType[TGames::SNAKE] = "arcade_snake.so";
    _assignType[TGames::MINESWEEPER] = "arcade_minesweeper.so";
    _assignType[TGames::NIBBLER] = "arcade_nibbler.so";
    _assignType[TGames::PACMAN] = "arcade_pacman.so";
    _assignType[TGames::QIX] = "arcade_qix.so";
    _assignType[TGames::CENTIPEDE] = "arcade_centipede.so";
    _assignType[TGames::SOLARFOX] = "arcade_solarfox.so";
    _assignType[TGames::SOKOBAN] = "arcade_sokoban.so";
    _assignType[TGames::SPACE] = "arcade_space.so";
    _assignType[TGames::TETRIS] = "arcade_tetris.so";
    _assignType[TGames::THE_SHOW] = "arcade_the_show.so";
    _gameDisplay["arcade_menu.so"] = "Menu";
    _gameDisplay["arcade_snake.so"] = "Snake";
    _gameDisplay["arcade_minesweeper.so"] = "Minesweeper";
    _gameDisplay["arcade_nibbler.so"] = "Nibbler";
    _gameDisplay["arcade_pacman.so"] = "Pacman";
    _gameDisplay["arcade_qix.so"] = "Qix";
    _gameDisplay["arcade_centipede.so"] = "Centipede";
    _gameDisplay["arcade_solarfox.so"] = "SolarFox";
    _gameDisplay["arcade_sokoban.so"] = "Sokoban";
    _gameDisplay["arcade_space.so"] = "Space";
    _gameDisplay["arcade_tetris.so"] = "Tetris";
    _gameDisplay["arcade_the_show.so"] = "The Show";
    for (const auto &[type, name] : _assignType) {
        _assignGame[name] = type;
    }
}

arcade::GameManager::~GameManager()
{
    if (_currentGame) {
        delete _currentGame;
        _currentGame = nullptr;
    }
    if (_currentHandle) {
        dlclose(_currentHandle);
        _currentHandle = nullptr;
    }
}

std::vector<std::string> arcade::GameManager::findGames(const std::string &gameDir)
{
    std::vector<std::string> gameNames;
    std::filesystem::path currentPath = gameDir;

    for (const auto &[type, gameName] : _assignType) {
        for (const auto &entry : std::filesystem::recursive_directory_iterator(currentPath)) {
            if (entry.is_regular_file() && entry.path().filename() == gameName) {
                if (gameName == "arcade_menu.so")
                    continue;
                _gamePaths[gameName] = entry.path().string();
                gameNames.push_back(gameName);
                break;
            }
        }
    }
    return gameNames;
}

void arcade::GameManager::loadGames(const std::string &gameDir)
{
    _gameNames = findGames(gameDir);
    if (_gameNames.empty()) {
        throw Error("No games found in directory: " + gameDir);
    }
    _currentGame = loadGame(_gamePaths[_gameNames[0]]);
    if (!_currentGame) {
        throw Error("Cannot load game: " + _gameNames[0]);
    }
}

arcade::IGames *arcade::GameManager::loadGame(const std::string &gamePath)
{
    if (_currentHandle) {
        if (_currentGame) {
            delete _currentGame;
            _currentGame = nullptr;
        }
        dlclose(_currentHandle);
        _currentHandle = nullptr;
    }
    _currentHandle = dlopen(gamePath.c_str(), RTLD_LAZY);
    if (!_currentHandle) {
        throw Error("Cannot open game: " + std::string(dlerror()));
    }
    IGames *(*entryPoint)();
    *(void**)(&entryPoint) = dlsym(_currentHandle, "entryPoint");
    if (!entryPoint) {
        dlclose(_currentHandle);
        _currentHandle = nullptr;
        throw Error("Cannot load symbol: " + std::string(dlerror()));

    }
    return entryPoint();
}

arcade::IGames *arcade::GameManager::nextGame()
{
    if (_gameNames.empty())
        return nullptr;
    _currentIndex = (_currentIndex + 1) % _gameNames.size();
    _currentGame = loadGame(_gamePaths[_gameNames[_currentIndex]]);
    return _currentGame;
}

arcade::IGames *arcade::GameManager::previousGame()
{
    if (_gameNames.empty())
        return nullptr;
    _currentIndex = (_currentIndex == 0) ? _gameNames.size() - 1 : _currentIndex - 1;
    _currentGame = loadGame(_gamePaths[_gameNames[_currentIndex]]);
    return _currentGame;
}

arcade::IGames *arcade::GameManager::getCurrentGame() const
{
    return _currentGame;
}

void arcade::GameManager::setCurrentGame(const std::string &gameName)
{
    auto displayIt = std::find_if(_gameDisplay.begin(), _gameDisplay.end(),
        [&gameName](const auto &pair) {
            return pair.second == gameName;
        });
    if (displayIt == _gameDisplay.end()) {
        throw Error("Game display name not found: " + gameName);
    }
    std::string actualGame = displayIt->first;
    auto it = _gamePaths.find(actualGame);
    if (it == _gamePaths.end()) {
        throw Error("Game not found: " + actualGame);
    }
    auto indexIt = std::find(_gameNames.begin(), _gameNames.end(), actualGame);
    if (indexIt == _gameNames.end()) {
        throw Error("Game name not found in _gameNames: " + actualGame);
    }
    _currentIndex = std::distance(_gameNames.begin(), indexIt);
    _currentGame = loadGame(it->second);
}

std::vector<std::string> arcade::GameManager::getDisplayNames() const
{
    std::vector<std::string> displayNames;
    for (const auto &gameName : _gameNames) {
        auto it = _gameDisplay.find(gameName);
        if (it != _gameDisplay.end()) {
            displayNames.push_back(it->second);
        }
    }
    return displayNames;
}
