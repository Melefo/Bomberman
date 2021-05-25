/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Prototype
*/

#include "Entity.hpp"

namespace Prototype
{
    Entity::Entity(const std::string& modelPath, RayLib::Vector3 pos) : model(std::make_unique<RayLib::Model>(modelPath)), position(pos)
    {

    }

    RayLib::Model& Entity::getModel()
    {
        return (*model);
    }

    RayLib::Vector3& Entity::getPosition()
    {
        return (position);
    }
}