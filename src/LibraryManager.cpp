/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** LibraryManager
*/

#include "LibraryManager.hpp"

arcade::LibraryManager::LibraryManager() : _currentHandle(nullptr), _currentIndex(0), _currentLib(nullptr)
{
    _assignType[TGraphics::NCURSES] = "arcade_ncurses.so";
    _assignType[TGraphics::SDL] = "arcade_sdl2.so";
    _assignType[TGraphics::NDK] = "arcade_ndk++.so";
    _assignType[TGraphics::AA] = "arcade_aalib.so";
    _assignType[TGraphics::CACA] = "arcade_libcaca.so";
    _assignType[TGraphics::ALLEGRO] = "arcade_allegro5.so";
    _assignType[TGraphics::X] = "arcade_xlib.so";
    _assignType[TGraphics::GTK] = "arcade_gtk+.so";
    _assignType[TGraphics::SFML] = "arcade_sfml.so";
    _assignType[TGraphics::IRRLICHT] = "arcade_irrlicht.so";
    _assignType[TGraphics::OPENGL] = "arcade_opengl.so";
    _assignType[TGraphics::VULKAN] = "arcade_vulkan.so";
    _assignType[TGraphics::QT] = "arcade_qt5.so";
    for (const auto &[type, name] : _assignType) {
        _assignLib[name] = type;
        _libNames.push_back(name);
        _libPaths[name] = "./lib/" + name;
    }
}

arcade::LibraryManager::~LibraryManager()
{
    if (_currentLib) {
        delete _currentLib;
        _currentLib = nullptr;
    }
    if (_currentHandle) {
        dlclose(_currentHandle);
        _currentHandle = nullptr;
    }
}

void arcade::LibraryManager::loadLibrary(const std::string &libPath)
{
    std::string libName = std::filesystem::path(libPath).filename().string();

    _currentLib = openLibrary(libPath);
    if (!_currentLib) {
        throw Error("Cannot load library: " + libPath);
    }
    if (std::find(_libNames.begin(), _libNames.end(), libName) == _libNames.end()) {
        _libNames.push_back(libName);
        _libPaths[libName] = libPath;
    }
    _currentIndex = std::distance(_libNames.begin(), std::find(_libNames.begin(), _libNames.end(), libName));
}

arcade::IGraphics *arcade::LibraryManager::openLibrary(const std::string &libPath)
{
    IGraphics *(*entryPoint)();

    if (_currentHandle) {
        if (_currentLib) {
            delete _currentLib;
            _currentLib = nullptr;
        }
        dlclose(_currentHandle);
        _currentHandle = nullptr;
    }
    _currentHandle = dlopen(libPath.c_str(), RTLD_LAZY);
    if (!_currentHandle) {
        throw Error("Cannot open library: " + std::string(dlerror()));
    }
    *(void**)(&entryPoint) = dlsym(_currentHandle, "entryPoint");
    if (!entryPoint) {
        dlclose(_currentHandle);
        _currentHandle = nullptr;
        throw Error("Cannot load symbol: " + std::string(dlerror()));
    }
    return entryPoint();
}

arcade::IGraphics *arcade::LibraryManager::nextLibrary()
{
    size_t attempts = 0;

    if (_libNames.empty())
        throw Error("No libraries loaded");
    do {
        _currentIndex = (_currentIndex + 1) % _libNames.size();
        try {
            _currentLib = openLibrary(_libPaths[_libNames[_currentIndex]]);
            return _currentLib;
        } catch (const Error &e) {
            attempts++;
        }
    } while (attempts < _libNames.size());
    throw Error("No valid libraries available");
}

arcade::IGraphics *arcade::LibraryManager::previousLibrary()
{
    size_t attempts = 0;

    if (_libNames.empty())
        throw Error("No libraries loaded");
    do {
        _currentIndex = (_currentIndex == 0) ? _libNames.size() - 1 : _currentIndex - 1;
        try {
            _currentLib = openLibrary(_libPaths[_libNames[_currentIndex]]);
            return _currentLib;
        } catch (const Error &e) {
            attempts++;
        }
    } while (attempts < _libNames.size());
    throw Error("No valid libraries available");
}

arcade::IGraphics *arcade::LibraryManager::getCurrentLibrary() const
{
    return _currentLib;
}

arcade::TGraphics arcade::LibraryManager::getCurrentType() const
{
    auto it = _assignLib.find(_libNames[_currentIndex]);

    if (it != _assignLib.end()) {
        return it->second;
    }
    throw Error("Library type not found");
}
