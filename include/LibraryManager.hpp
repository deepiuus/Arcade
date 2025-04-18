/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** LibraryManager
*/

#ifndef LIBRARY_MANAGER_HPP_
#define LIBRARY_MANAGER_HPP_

#include "IGraphics.hpp"

namespace arcade {
    class LibraryManager {
        public:
            LibraryManager();
            ~LibraryManager();
            void loadLibrary(const std::string &libPath);
            IGraphics *nextLibrary();
            IGraphics *previousLibrary();
            IGraphics *getCurrentLibrary() const;
            TGraphics getCurrentType() const;
        private:
            void *_currentHandle;
            size_t _currentIndex;
            IGraphics *_currentLib;
            IGraphics *openLibrary(const std::string &libPath);
            std::map<TGraphics, std::string> _assignType;
            std::map<std::string, TGraphics> _assignLib;
            std::map<std::string, std::string> _libPaths;
            std::vector<std::string> _libNames;
    };
}

#endif /* !LIBRARY_MANAGER_HPP_ */
