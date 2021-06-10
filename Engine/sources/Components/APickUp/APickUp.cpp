/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** APickUp
*/

#include "APickUp.hpp"

namespace Component
{
    APickUp::APickUp(ECS::Entity& entity) : _entity(entity)
    {
    }

    void APickUp::FixedUpdate(ECS::Entity& entity)
    {
        std::vector<std::reference_wrapper<Collider>> colliders = entity.OfType<Collider>();

        for (Collider& col : colliders) {
            if (col.IsColliding()) {
                OnPickup(col.GetCollision());
            }
        }
    }
}
