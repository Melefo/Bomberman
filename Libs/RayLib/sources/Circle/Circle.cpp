/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Circle
*/

#include "Circle.hpp"

namespace RayLib
{
    Circle::Circle(RayLib::Vector2<float> center, float radius) :
    _center(center), _radius(radius)
    {
    }

    const RayLib::Vector2<float> Circle::GetCenter(void) const
    {
        return (_center);
    }

    float Circle::GetRadius(void) const
    {
        return (_radius);
    }

    void Circle::SetCenter(RayLib::Vector2<float> center)
    {
        _center = center;
    }

    void Circle::SetRadius(float radius)
    {
        _radius = radius;
    }

}


