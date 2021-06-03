/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"
#include "Transform.hpp"
#include <iostream>

namespace Component
{
    RenderSystem::RenderSystem()
    {
        AddDependency<Transform>();
        AddDependency<Renderer>();
    }

    void RenderSystem::Update(double dt, ECS::Entity& entity)
    {
        Renderer& renderer = entity.GetComponent<Renderer>();
        Transform& transform = entity.GetComponent<Transform>();
        RayLib::Model& model = renderer.GetModel();

        (void) dt;
        model.DrawEx(transform.position, transform.rotation, 0.0f, transform.scale, WHITE);
    }
}