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
        vector3.x = x;
        vector3.y = 0;
        vector3.z = 0;
    }

    Vector3::Vector3(float x, float y)
    {
        vector3.x = x;
        vector3.y = y;
        vector3.z = 0;
    }

    Vector3::Vector3(float x, float y, float z)
    {
        vector3.x = x;
        vector3.y = y;
        vector3.z = z;
    }

    Vector3::Vector3(const ::Vector3 &vec)
    {
        vector3.x = vec.x;
        vector3.y = vec.y;
        vector3.z = vec.z;
    }

    Vector3::~Vector3()
    {

    }

    Vector3& Vector3::operator=(const ::Vector3 &vec)
    {
        vector3.x = vec.x;
        vector3.y = vec.y;
        vector3.z = vec.z;
        return (*this);
    }
}