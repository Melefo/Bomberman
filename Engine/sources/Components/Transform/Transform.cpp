/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Transform
*/

#include "Transform.hpp"

namespace Component
{
    Transform::Transform(RayLib::Vector3 startPos, RayLib::Vector3 startRot, RayLib::Vector3 startScale):
    position(startPos), rotation(startRot), scale(startScale)
    {
    }

    std::ostream& Transform::operator<<(std::ostream& stream)
    {
        // save position
        // save rotation
        // save scale
        return (stream);
    }

}

