/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AController
*/

#include "AController.hpp"

namespace Component
{
    AController::AController(ECS::Entity& attatchedEntity, float speed, float delay) : _movement(attatchedEntity, speed), _dropBomb(attatchedEntity, delay)
    {
    }

    Component::Movement& AController::GetMovement()
    {
        return (_movement);
    }

    Component::DropBomb& AController::GetDropBomb()
    {
        return (_dropBomb);
    }
}