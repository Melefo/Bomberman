/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Transform
*/

#include "Transform.hpp"

namespace Prototype
{
    Transform::Transform(RayLib::Vector3 startPos, RayLib::Vector3 startRot, RayLib::Vector3 startScale):
    position(startPos), rotation(startRot), scale(startScale)
    {
    }
}

