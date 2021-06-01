/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Collider
*/

#include "Collider.hpp"
#include <iostream>

namespace Prototype
{
    Collider::Collider(ECS::Entity& attatchedEntity, ECS::Coordinator& coordinator)
     : _otherEntities(coordinator.GetEntities()), _myEntity(attatchedEntity)
    {
    }

    bool Collider::IsColliding()
    {
        return (false);
    }

}

