/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsSystem
*/

#include "PhysicsSystem.hpp"
#include "Transform.hpp"
#include "Collider.hpp"
#include "GameConfiguration.hpp"
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

    void PhysicsSystem::Update(double, ECS::Entity& entity)
    {
        if (Engine::GameConfiguration::GetDebugMode() == true) {
            std::vector<std::reference_wrapper<Collider>> colliders = entity.OfType<Collider>();
            for (auto it = colliders.begin(); it != colliders.end(); it++) {
                it->get().DrawLines();
            }
        }
    }
}