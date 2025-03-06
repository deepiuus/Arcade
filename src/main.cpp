/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Main
*/

#include <dlfcn.h>
#include <iostream>
#include <string>
#include "IGraphics.hpp"

enum class TGraphics {
    NCURSES,
    SDL,
    ALLEGRO
};

std::string getPath(TGraphics type)
{
    switch (type) {
        case TGraphics::NCURSES:
            return "./lib/libarcadeNcurses.so";
        case TGraphics::SDL:
            return "./lib/libarcadeSdl.so";
        case TGraphics::ALLEGRO:
            return "./lib/libarcadeAllegro.so";
        default:
            return "";
    }
}

IGraphics* loadLib(TGraphics type, void **handle)
{
    // Fermer l'ancienne bibliothèque si elle existe
    if (*handle) {
        dlclose(*handle);
        *handle = nullptr;
    }

    // Charger la nouvelle bibliothèque
    *handle = dlopen(getPath(type).c_str(), RTLD_LAZY);
    if (!*handle) {
        std::cerr << "Cannot open library: " << dlerror() << std::endl;
        return nullptr;
    }

    // Charger la fonction de création
    IGraphics* (*createGraphics)();
    *(void**)(&createGraphics) = dlsym(*handle, "createGraphics");
    if (!createGraphics) {
        std::cerr << "Cannot load symbol: " << dlerror() << std::endl;
        dlclose(*handle);
        *handle = nullptr;
        return nullptr;
    }
    return createGraphics();
}

int main()
{
    void *handle = nullptr;
    TGraphics currentLib = TGraphics::SDL;
    IGraphics *graphics = loadLib(currentLib, &handle);

    if (!graphics)
        return 1;
    while (graphics->isRunning()) {
        graphics->Action();
        graphics->Clear();
        graphics->Display();

        // Exemple: changer de bibliothèque avec une touche
        // (à implémenter dans la classe graphique)
        /*
        if (switchLibraryRequested) {
            delete graphics;
            currentLib = TGraphics::SDL;  // ou une autre bibliothèque
            graphics = loadLib(currentLib, &handle);
            if (!graphics)
                break;
        }
        */
    }
    delete graphics;
    if (handle)
        dlclose(handle);
    return 0;
}
