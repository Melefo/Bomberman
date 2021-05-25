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
        hit = false;
        distance = 0.0f;
        position = Vector3();
        normal = Vector3();
    }

    RayHitInfo::~RayHitInfo()
    {

    }

    RayHitInfo::RayHitInfo(const RayHitInfo& other)
    {
        hit = other.hit;
        distance = other.distance;
        position = other.position;
        normal = other.normal;
    }

    RayHitInfo::RayHitInfo(const ::RayHitInfo& other)
    {
        hit = other.hit;
        distance = other.distance;
        position = other.position;
        normal = other.normal;
    }

    RayHitInfo& RayHitInfo::operator=(const RayHitInfo& other)
    {
        hit = other.hit;
        distance = other.distance;
        position = other.position;
        normal = other.normal;
        return (*this);
    }

    RayHitInfo& RayHitInfo::operator=(const ::RayHitInfo& other)
    {
        hit = other.hit;
        distance = other.distance;
        position = other.position;
        normal = other.normal;
        return (*this);
    }

    ::RayHitInfo RayHitInfo::GetHitInfo(void)
    {
        ::RayHitInfo info = {hit,
                             distance,
                             position.getVector3(),
                             normal.getVector3()};
        return (info);
    }
}