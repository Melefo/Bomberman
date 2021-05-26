/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** MoveSystem
*/

#include "MoveSystem.hpp"
#include "OjectComponent.hpp"
#include <iostream>

MoveSystem::MoveSystem()
{
    this->AddDependency<OjectComponent>();
}

void MoveSystem::Update(double dt, ECS::Entity &entity)
{
    OjectComponent &obj = entity.GetComponent<OjectComponent>();

    obj.position.x += (rand() % 100) * dt;
    obj.position.y += (rand() % 100) * dt;

    //std::cout << "raylib dt: " << ::GetFrameTime() << std::endl;
    //std::cout << "victor dt: " << dt << std::endl;

    obj.model.Draw(obj.position, obj.size, RED);
}