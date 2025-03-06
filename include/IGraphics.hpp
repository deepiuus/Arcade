/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IGraphics
*/

#ifndef IGRAPHICS_HPP_
#define IGRAPHICS_HPP_

class IGraphics {
    public:
        virtual ~IGraphics() = default;
        virtual void Init() = 0;
        virtual bool isRunning() = 0;
        virtual void Action() = 0;
        virtual void Clear() = 0;
        virtual void Display() = 0;
        virtual void Nuke() = 0;
};

#endif /* !IGRAPHICS_HPP_ */
