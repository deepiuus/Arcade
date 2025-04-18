/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Main
*/

#include "IGraphics.hpp"
#include "IGames.hpp"
#include "LibraryManager.hpp"
#include "GameManager.hpp"
#include "../lib/Games/menu/menu.hpp"
#include <thread>
#include <chrono>

int switchLibrary(arcade::KeyBind key, arcade::LibraryManager &libManager,
    arcade::IGraphics *&graphics, arcade::GameManager &gameManager, arcade::IGames *&game)
{
    arcade::IGraphics *tmp = nullptr;

    switch (key) {
        case arcade::KeyBind::ESC:
            graphics->Nuke();
            return 0;
        case arcade::KeyBind::A_KEY:
            graphics->Nuke();
            tmp = libManager.previousLibrary();
            if (!tmp)
                return 84;
            graphics = tmp;
            graphics->Init();
            break;
        case arcade::KeyBind::Z_KEY:
            graphics->Nuke();
            tmp = libManager.nextLibrary();
            if (!tmp)
                return 84;
            graphics = tmp;
            graphics->Init();
            break;
        case arcade::KeyBind::Q_KEY:
            gameManager.previousGame();
            if (libManager.getCurrentType() == arcade::TGraphics::NCURSES)
                graphics->Clear();
            game = gameManager.getCurrentGame();
            break;
        case arcade::KeyBind::S_KEY:
            gameManager.nextGame();
            if (libManager.getCurrentType() == arcade::TGraphics::NCURSES)
                graphics->Clear();
            game = gameManager.getCurrentGame();
            break;
        default:
            break;
    }
    return 1;
}

void Run(arcade::LibraryManager &libManager, arcade::IGraphics *graphics,
    arcade::GameManager &gameManager, arcade::IGames *game, arcade::Menu &menu)
{
    auto lastFrameTime = std::chrono::steady_clock::now();
    const auto targetFrameTime = std::chrono::milliseconds(16);
    int lives = 3;

    while (true) {
        auto entities = game->getDisplay(libManager.getCurrentType());
        graphics->Display(entities);
        if (libManager.getCurrentType() != arcade::TGraphics::NCURSES)
            graphics->Clear();
        arcade::KeyBind key = graphics->getKey();
        bool inputProcessed = false;
        if (key != arcade::KeyBind::NONE) {
            game->setKey(key);
            if (!switchLibrary(key, libManager, graphics, gameManager, game))
                return;
            inputProcessed = true;
        }
        arcade::Menu *menuGame = dynamic_cast<arcade::Menu*>(game);
        if (menuGame && menuGame->isGameSelected()) {
            std::string selectedGame = menuGame->getActGame();
            gameManager.setCurrentGame(selectedGame);
            game = gameManager.getCurrentGame();
            menuGame->resetGame();
            lives = 3;
        }
        if (game->getActGame() == "GAME OVER") {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            lives--;
            if (lives > 0) {
                game = gameManager.getCurrentGame();
                game->resetGame();
                graphics->Clear();
                continue;
            } else {
                game = &menu;
                menu.resetGameSelected();
                lives = 3;
                graphics->Clear();
            }
        }
        std::string sound = game->getSound(libManager.getCurrentType());
        if (!sound.empty())
            graphics->PlaySound(sound);
        auto currentTime = std::chrono::steady_clock::now();
        auto frameTime = currentTime - lastFrameTime;
        if (!inputProcessed && frameTime < targetFrameTime)
            std::this_thread::sleep_for(targetFrameTime - frameTime);
        lastFrameTime = std::chrono::steady_clock::now();
    }
}

int main(int ac, char **av)
{
    arcade::IGraphics *graphics;
    arcade::LibraryManager libManager;
    arcade::GameManager gameManager;

    if (ac != 2) {
        std::cerr << "Usage: ./arcade <library_path>" << std::endl;
        return 84;
    }
    try {
        libManager.loadLibrary(av[1]);
        graphics = libManager.getCurrentLibrary();
        graphics->Init();
        gameManager.loadGames("lib/");
        arcade::Menu menu(gameManager.getDisplayNames());
        arcade::IGames *game = &menu;
        Run(libManager, graphics, gameManager, game, menu);
    } catch (const arcade::Error &e) {
        std::cerr << "Arcade error: " << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << "Standard exception: " << e.what() << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
        return 84;
    }
    return 0;
}
