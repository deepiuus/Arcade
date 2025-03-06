/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Allegro
*/

#include "allegro.hpp"

AllegroLib::AllegroLib() : display(nullptr), event_queue(nullptr), running(false)
{
    Init();
}

AllegroLib::~AllegroLib()
{
    Nuke();
}

void AllegroLib::Init()
{
    al_init();
    al_install_keyboard();
    display = al_create_display(800, 600);
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    running = true;
}

bool AllegroLib::isRunning()
{
    return running;
}

void AllegroLib::Action()
{
    al_wait_for_event(event_queue, &event);
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE 
    || (event.type == ALLEGRO_EVENT_KEY_DOWN 
    && (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE 
    || event.keyboard.keycode == ALLEGRO_KEY_Q))) {
        running = false;
    }
}

void AllegroLib::Clear()
{
    al_clear_to_color(al_map_rgb(255, 255, 255));
}

void AllegroLib::Display()
{
    al_flip_display();
}

void AllegroLib::Nuke()
{
    if (event_queue)
        al_destroy_event_queue(event_queue);
    if (display)
        al_destroy_display(display);
}
