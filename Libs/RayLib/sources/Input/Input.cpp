/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Input
*/

#include "Input.hpp"

namespace RayLib
{
    Input::Input(Vector2<int> horizontalKeys, Vector2<int> verticalKeys) : _horizontalAxis(horizontalKeys), _verticalAxis(verticalKeys)
    {
    }

    Input::Input(const Input& other) :
    _horizontalAxis(other._horizontalAxis), _verticalAxis(other._verticalAxis)
    {
    }

    Input& Input::operator=(const Input& other)
    {
        _horizontalAxis = other._horizontalAxis;
        _verticalAxis = other._verticalAxis;
        return (*this);
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

    bool Input::IsKeyPressed(int key)
    {
        return (::IsKeyPressed(key));
    }

    int Input::GetKeyPressed(void)
    {
        return (::GetKeyPressed());
    }

    int Input::GetCharPressed(void)
    {
        return (::GetCharPressed());
    }

    Vector2<int> Input::GetHorizontalKeys(void)
    {
        return (_horizontalAxis);
    }

    Vector2<int> Input::GetVerticalKeys(void)
    {
        return (_verticalAxis);
    }
}