/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** EntitySerializer
*/

#include "EntitySerializer.hpp"
#include <iostream>

EntitySerializer::EntitySerializer(const std::string &filepath) : XMLGenerator(filepath)
{
}

void EntitySerializer::SaveEntities()
{
    // get coordinator
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

    // get entities
    const std::list<std::unique_ptr<ECS::Entity>>& entities = coordinator->GetEntities();

    // loop and save entity
    for (const std::unique_ptr<ECS::Entity>& entity : entities) {
        SaveEntity(*entity.get());
    }
}

void EntitySerializer::SaveEntity(ECS::Entity& entity)
{
    addTag("Entity");
    if (entity.HasComponent<Component::Transform>())
        SerializeTransform(entity.GetComponent<Component::Transform>());

    CloseTag("Entity");
}

void EntitySerializer::SerializeTransform(Component::Transform& transform)
{
    addTag("Transform");
    addTag("position");
    addValue("x", transform.position.x);
    addValue("y", transform.position.y);
    addValue("z", transform.position.z);
    CloseTag("position");
    addTag("rotation");
    addValue("x", transform.rotation.x);
    addValue("y", transform.rotation.y);
    addValue("z", transform.rotation.z);
    CloseTag("rotation");
    addTag("scale");
    addValue("x", transform.scale.x);
    addValue("y", transform.scale.y);
    addValue("z", transform.scale.z);
    CloseTag("scale");
    CloseTag("Transform");
}
