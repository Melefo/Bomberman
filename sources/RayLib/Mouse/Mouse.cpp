/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Mouse
*/

#include "Mouse.hpp"

namespace RayLib
{

    Mouse::Mouse()
    {
    }

    Mouse::~Mouse()
    {
    }

    Vector2<float> Mouse::getPosition()
    {
        ::Vector2 mousePos = GetMousePosition();

        return (Vector2<float>(mousePos));
    }

    bool Mouse::isButtonDown(int button)
    {
        return (IsMouseButtonDown(button));
    }

    bool Mouse::isButtonUp(int button)
    {
        return (IsMouseButtonUp(button));
    }
}