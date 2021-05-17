/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Vector2
*/

#include "Vector2.hpp"

namespace RayLib
{

    Vector2::Vector2(float newX)
    {
        x = newX;
        y = 0;
    }

    Vector2::Vector2(float newX, float newY)
    {
        x = newX;
        y = newY;
    }

    Vector2::Vector2(const Vector2 &vec)
    {
        x = vec.x;
        y = vec.y;
    }

    Vector2::~Vector2()
    {

    }

    Vector2& Vector2::operator=(const Vector2 &vec)
    {
        x = vec.x;
        y = vec.y;
        return (*this);
    }
}