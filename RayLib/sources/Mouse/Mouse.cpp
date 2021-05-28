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

    Vector2<float> Mouse::GetPosition()
    {
        ::Vector2 mousePos = GetMousePosition();

        return (Vector2<float>(mousePos));
    }

    bool Mouse::IsButtonDown(int button)
    {
        return (::IsMouseButtonDown(button));
    }

    bool Mouse::IsButtonUp(int button)
    {
        return (IsMouseButtonUp(button));
    }

    bool Mouse::IsButtonPressed(int button)
    {
        return (::IsMouseButtonPressed(button));
    }

    bool Mouse::IsButtonReleased(int button)
    {
        return (::IsMouseButtonReleased(button));
    }
}