/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsSystem
*/

#include "PhysicsSystem.hpp"
#include "Transform.hpp"
#include <iostream>

namespace Component
{
    PhysicsSystem::PhysicsSystem()
    {
        AddDependency<PhysicsBody>();
        AddDependency<Transform>();
    }

    void PhysicsSystem::FixedUpdate(ECS::Entity &entity)
    {
        PhysicsBody &physicsBody = entity.GetComponent<PhysicsBody>();
        Transform &transform = entity.GetComponent<Transform>();

        // !float fixedDeltaTime = 0.02f;

        transform.position += physicsBody.velocity;
    }
}