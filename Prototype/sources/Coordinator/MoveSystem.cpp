/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** MoveSystem
*/

#include "MoveSystem.hpp"
#include "ObjectComponent.hpp"
#include <iostream>

MoveSystem::MoveSystem()
{
    this->AddDependency<ObjectComponent>();
}

void MoveSystem::Update(double dt, ECS::Entity &entity)
{
    ObjectComponent &obj = entity.GetComponent<ObjectComponent>();

    obj.position.x += (rand() % 10) * dt;
    obj.position.y += (rand() % 10) * dt;

    //std::cout << "raylib dt: " << ::GetFrameTime() << std::endl;
    //std::cout << "victor dt: " << dt << std::endl;

    obj.model.Draw(obj.position, obj.size, RED);
}