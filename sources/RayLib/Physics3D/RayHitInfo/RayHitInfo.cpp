/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RayHitInfo
*/

#include "RayHitInfo.hpp"

namespace RayLib
{
    RayHitInfo::RayHitInfo()
    {
        _hit = false;
        _distance = 0.0f;
        _position = Vector3();
        _normal = Vector3();
    }

    RayHitInfo::~RayHitInfo()
    {

    }

    RayHitInfo::RayHitInfo(const RayHitInfo& other)
    {
        _hit = other._hit;
        _distance = other._distance;
        _position = other._position;
        _normal = other._normal;
    }

    RayHitInfo::RayHitInfo(const ::RayHitInfo& other)
    {
        _hit = other.hit;
        _distance = other.distance;
        _position = other.position;
        _normal = other.normal;
    }

    RayHitInfo& RayHitInfo::operator=(const RayHitInfo& other)
    {
        _hit = other._hit;
        _distance = other._distance;
        _position = other._position;
        _normal = other._normal;
        return (*this);
    }

    RayHitInfo& RayHitInfo::operator=(const ::RayHitInfo& other)
    {
        _hit = other.hit;
        _distance = other.distance;
        _position = other.position;
        _normal = other.normal;
        return (*this);
    }

    ::RayHitInfo RayHitInfo::GetHitInfo(void)
    {
        ::RayHitInfo info = {_hit,
                             _distance,
                             _position.getVector3(),
                             _normal.getVector3()};
        return (info);
    }

    bool RayHitInfo::HasHit(void)
    {
        return (_hit);
    }

    float RayHitInfo::GetDistance(void)
    {
        return (_distance);
    }

    Vector3& RayHitInfo::GetPosition(void)
    {
        return (_position);
    }

    Vector3& RayHitInfo::GetNormal(void)
    {
        return (_normal);
    }
}