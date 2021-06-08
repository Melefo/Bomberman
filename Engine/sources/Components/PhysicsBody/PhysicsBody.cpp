/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsBody
*/

#include "PhysicsBody.hpp"

namespace Component
{
    PhysicsBody::PhysicsBody(RayLib::Vector3 startVelocity)
    {
        velocity = startVelocity;
    }

    std::ostream& PhysicsBody::operator<<(std::ostream& stream)
    {
        // save velocity
        return (stream);
    }
}