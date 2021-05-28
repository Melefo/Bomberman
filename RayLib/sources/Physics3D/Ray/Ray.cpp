/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Ray
*/

#include "Ray.hpp"

namespace RayLib
{
    Ray::Ray()
    {
        _position = Vector3(0.0f, 0.0f, 0.0f);
        _direction = Vector3(0.0f, 0.0f, 0.0f);
    }

    Ray::Ray(Vector3 position, Vector3 direction)
    {
        _position = position;
        _direction = direction;
    }

    Ray::~Ray()
    {
    }

    Ray::Ray(const Ray& other)
    {
        _position = other._position;
        _direction = other._direction;
    }

    Ray::Ray(const ::Ray& other)
    {
        _position = other.position;
        _direction = other.direction;
    }


    Ray& Ray::operator=(const Ray& other)
    {
        _position = other._position;
        _direction = other._direction;
        return (*this);
    }

    Vector3& Ray::GetPosition(void)
    {
        return (_position);
    }

    Vector3& Ray::GetDirection(void)
    {
        return (_direction);
    }

    ::Ray Ray::GetRay(void)
    {
        ::Ray ray = {_position.getVector3(), _direction.getVector3()};
        return (ray);
    }
}
