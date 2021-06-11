/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** APickUp
*/

#include "APickUp.hpp"

namespace Component
{
    APickUp::APickUp(ECS::Entity& entity, float pickupRadius)
    : _entity(entity), _pickupRadius(pickupRadius), _coordinator(*(ECS::Coordinator::GetInstance().get()))
    {
    }

    void APickUp::FixedUpdate(ECS::Entity& entity)
    {
        /*std::vector<std::reference_wrapper<Collider>> colliders = entity.OfType<Collider>();

        for (Collider& col : colliders) {
            if (col.IsColliding()) {
                OnPickup(col.GetCollision());
            }
        }*/

        if (entity.HasComponent<Transform>()) {
            Transform& transform = entity.GetComponent<Transform>();
            std::vector<std::reference_wrapper<ECS::Entity>> entities = CollisionSystem::OverlapSphere(_coordinator, transform.position, _pickupRadius);

            

            if (entities.size() > 0) {
                OnPickup(entities[0]);
            }
        }
    }
}
