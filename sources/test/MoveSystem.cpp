/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** MoveSystem
*/

#include "MoveSystem.hpp"
#include "OjectComponent.hpp"

MoveSystem::MoveSystem()
{
    this->AddDependency<OjectComponent>();
}

void MoveSystem::Update(double dt, ECS::Entity &entity)
{
    OjectComponent &obj = entity.GetComponent<OjectComponent>();

    obj.position.x += 1.0 * dt;
    obj.position.y += 1.0 * dt;
    obj.model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, obj.texture);
    obj.model.Draw(obj.position, obj.size, WHITE);
}