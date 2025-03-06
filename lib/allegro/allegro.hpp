/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Allegro
*/

#ifndef ALLEGRO_LIB_HPP_
#define ALLEGRO_LIB_HPP_

#include <allegro5/allegro.h>
#include "IGraphics.hpp"

class AllegroLib : public IGraphics {
    public:
        AllegroLib();
        ~AllegroLib() override;

        void Init() override;
        bool isRunning() override;
        void Action() override;
        void Clear() override;
        void Display() override;
        void Nuke() override;

    private:
        ALLEGRO_DISPLAY *display;
        ALLEGRO_EVENT event;
        ALLEGRO_EVENT_QUEUE *event_queue;
        bool running;
};

extern "C" IGraphics *createGraphics() {
    return new AllegroLib();
}

#endif /* !ALLEGRO_LIB_HPP_ */
