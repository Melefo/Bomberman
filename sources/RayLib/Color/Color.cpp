/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Color
*/

#include "Color.hpp"

namespace RayLib
{
    Color::Color()
    {
        r = 0;
        g = 0;
        b = 0;
        a = 0;
    }

    Color::Color(const Vector3& hsv)
    {
        r = hsv.x;
        g = hsv.y;
        b = hsv.z;
        a = 0;
    }

    Color::Color(const Color& col)
    {
        r = col.r;
        g = col.g;
        b = col.b;
        a = col.a;
    }

    Color& Color::operator=(const Color &col)
    {
        r = col.r;
        g = col.g;
        b = col.b;
        a = col.a;
        return (*this);
    }


    Color::~Color()
    {
    }


}