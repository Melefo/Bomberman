/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Vector4
*/

#include "Vector4.hpp"

namespace RayLib
{

    Vector4::Vector4()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    Vector4::Vector4(float newX)
    {
        x = newX;
        y = 0;
        z = 0;
        w = 0;
    }

    Vector4::Vector4(float newX, float newY)
    {
        x = newX;
        y = newY;
        z = 0;
        w = 0;
    }

    Vector4::Vector4(float newX, float newY, float newZ)
    {
        x = newX;
        y = newY;
        z = newZ;
        w = 0;
    }

    Vector4::Vector4(float newX, float newY, float newZ, float newW)
    {
        x = newX;
        y = newY;
        z = newZ;
        w = newW;
    }

    Vector4::Vector4(const Vector4 &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = vec.w;
    }

    Vector4::Vector4(const ::Vector4 &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = vec.w;
    }

    ::Vector4 Vector4::getVector4(void)
    {
        ::Vector4 vec4 = {x, y, z, w};

        return (vec4);
    }

    Vector4& Vector4::operator=(const Vector4& vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = vec.w;
        return (*this);
    }
}