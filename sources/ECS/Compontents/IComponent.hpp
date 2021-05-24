/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include <string>

class IComponent
{
    public:
        IComponent() = default;
        virtual ~IComponent() = default;
        virtual const std::string GetName() const = 0;
};

#endif /* !ICOMPONENT_HPP_ */