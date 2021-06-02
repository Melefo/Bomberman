/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"
#include <iostream>

namespace Prototype
{
    std::unique_ptr<std::reference_wrapper<CollisionSystem>> CollisionSystem::_colSystem = nullptr;

    CollisionSystem::CollisionSystem(ECS::Coordinator& coordinator) : _coordinator(coordinator)
    {
        AddDependency<Collider>();
        SetSystem(*this);
    }

    void CollisionSystem::SetSystem(CollisionSystem& colsystem)
    {
        _colSystem = std::make_unique<std::reference_wrapper<CollisionSystem>>(colsystem);
    }

    std::vector<std::reference_wrapper<ECS::Entity>> CollisionSystem::OverlapSphere(RayLib::Vector3 center, float radius)
    {
        ECS::Coordinator& coordinator = CollisionSystem::_colSystem->get().GetCoordinator();
        const std::list<std::unique_ptr<ECS::Entity>>& entities = coordinator.GetEntities();
        std::vector<std::reference_wrapper<ECS::Entity>> collisions;

        for (auto it = entities.begin(); it != entities.end(); it++) {
            std::vector<std::reference_wrapper<Collider>> colliders = it->get()->OfType<Collider>();

            for (auto col = colliders.begin(); col != colliders.end(); col++) {
                if (col->get().CheckCollision(center, radius))
                    collisions.push_back(*(it->get()));
            }
        }
        return (collisions);
    }

    ECS::Coordinator& CollisionSystem::GetCoordinator()
    {
        return (_coordinator);
    }

}
