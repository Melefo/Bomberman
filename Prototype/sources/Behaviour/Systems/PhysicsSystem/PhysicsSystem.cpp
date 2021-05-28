/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsSystem
*/

#include "PhysicsSystem.hpp"
#include "PhysicsBody.hpp"
#include "Transform.hpp"
#include <iostream>

namespace Prototype
{
    PhysicsSystem::PhysicsSystem()
    {
        AddDependency<PhysicsBody>();
        AddDependency<Transform>();
    }

    void PhysicsSystem::Update(double dt, ECS::Entity &entity)
    {
        PhysicsBody &physicsBody = entity.GetComponent<PhysicsBody>();
        Transform &transform = entity.GetComponent<Transform>();

        transform.position += physicsBody.velocity * dt;
    }
}