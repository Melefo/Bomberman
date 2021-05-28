/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Input
*/

#include "Input.hpp"

namespace RayLib
{
    Input::Input(Vector2<int> horizontalKeys, Vector2<int> verticalKeys)
    {
        _horizontalAxis = horizontalKeys;
        _verticalAxis = verticalKeys;
    }

    float Input::GetHorizontalAxis(void)
    {
        if (IsKeyDown(_horizontalAxis.x))
            return (-1.0f);
        else if (IsKeyDown(_horizontalAxis.y))
            return (1.0f);
        return (0.0f);
    }

    float Input::GetVerticalAxis(void)
    {
        if (IsKeyDown(_verticalAxis.x))
            return (-1.0f);
        else if (IsKeyDown(_verticalAxis.y))
            return (1.0f);
        return (0.0f);
    }

    bool Input::IsKeyDown(int key)
    {
        return (::IsKeyDown(key));
    }

    int Input::GetKeyPressed(void)
    {
        // ! il y a une queue donc faire un while ?
        return (::GetKeyPressed());
    }


    Input::~Input()
    {

    }
}