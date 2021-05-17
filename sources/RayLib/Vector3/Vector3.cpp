/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Vector3
*/

#include "Vector3.hpp"

namespace RayLib
{

    Vector3::Vector3(float x)
    {
        x = x;
        y = 0;
        z = 0;
    }

    Vector3::Vector3(float x, float y)
    {
        x = x;
        y = y;
        z = 0;
    }

    Vector3::Vector3(float x, float y, float z)
    {
        x = x;
        y = y;
        z = z;
    }

    Vector3::Vector3(const Vector3 &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    Vector3::~Vector3()
    {

    }

    Vector3& Vector3::operator=(const Vector3 &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        return (*this);
    }
}