/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RayCollision
*/

#include "RayCollision.hpp"

namespace RayLib
{
    RayCollision::RayCollision()
    {
        _hit = false;
        _distance = 0.0f;
        _point = Vector3();
        _normal = Vector3();
    }

    RayCollision::RayCollision(const RayCollision& other)
    {
        _hit = other._hit;
        _distance = other._distance;
        _point = other._point;
        _normal = other._normal;
    }

    RayCollision::RayCollision(const ::RayCollision& other)
    {
        _hit = other.hit;
        _distance = other.distance;
        _point = other.point;
        _normal = other.normal;
    }

    RayCollision& RayCollision::operator=(const RayCollision& other)
    {
        _hit = other._hit;
        _distance = other._distance;
        _point = other._point;
        _normal = other._normal;
        return (*this);
    }

    RayCollision& RayCollision::operator=(const ::RayCollision& other)
    {
        _hit = other.hit;
        _distance = other.distance;
        _point = other.point;
        _normal = other.normal;
        return (*this);
    }

    ::RayCollision RayCollision::GetHitInfo(void)
    {
        ::RayCollision info = {_hit,
                             _distance,
                             _point.getVector3(),
                             _normal.getVector3()};
        return (info);
    }

    bool RayCollision::HasHit(void)
    {
        return (_hit);
    }

    float RayCollision::GetDistance(void)
    {
        return (_distance);
    }

    Vector3& RayCollision::GetPosition(void)
    {
        return (_point);
    }

    Vector3& RayCollision::GetNormal(void)
    {
        return (_normal);
    }
}