/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Rectangle
*/

#include "Rectangle.hpp"

namespace RayLib
{
    Rectangle::Rectangle(float newX, float newY, float newWidth, float newHeight)
    {
        x = newX;
        y = newY;
        width = newWidth;
        height = newHeight;
    }

    Rectangle::Rectangle(const Rectangle& other)
    {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
    }

    Rectangle::Rectangle(const ::Rectangle& other)
    {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
    }

    Rectangle& Rectangle::operator=(const Rectangle& other)
    {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
        return (*this);
    }

    Rectangle& Rectangle::operator=(const ::Rectangle& other)
    {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
        return (*this);
    }

    ::Rectangle Rectangle::GetRectangle()
    {
        ::Rectangle rect = {x, y, width, height};

        return (rect);
    }

}

