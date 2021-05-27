/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsBody
*/

#include "PhysicsBody.hpp"

namespace Prototype
{
    PhysicsBody::PhysicsBody(RayLib::Vector3 startVelocity)
    {
        velocity = startVelocity;
    }
}