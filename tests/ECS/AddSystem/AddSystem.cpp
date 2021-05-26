/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** AddSystem
*/

#include "AddSystem.hpp"

AddSystem::AddSystem()
{
    this->AddDependency<StorageComponent>();
}

void AddSystem::Update(double, ECS::Entity &entity)
{
    StorageComponent &storage = entity.GetComponent<StorageComponent>();

    storage.value++;
}