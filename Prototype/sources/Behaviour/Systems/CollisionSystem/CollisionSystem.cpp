/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

namespace Prototype
{
    CollisionSystem::CollisionSystem(ECS::Coordinator& coordinator) : _coordinator(coordinator)
    {
        AddDependency<Collider>();
    }

    //std::vector<std::reference_wrapper<ECS::Entity>> CollisionSystem::OverlapSphere(RayLib::Vector3 center, float radius)
    //{
    //    _coordinator.GetEntities();
    //}
}
