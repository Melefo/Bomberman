/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Collider
*/

#include "Collider.hpp"
#include <iostream>

namespace Component
{
    Collider::Collider(ECS::Entity& attatchedEntity, std::vector<std::string> collisionMask)
     : _otherEntities(ECS::Coordinator::GetInstance("", 0.02f)->GetEntities()), _myEntity(attatchedEntity), _collisionMask(collisionMask)
    {

    }
}
