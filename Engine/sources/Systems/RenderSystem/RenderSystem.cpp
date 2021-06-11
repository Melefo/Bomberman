/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"
#include "Transform.hpp"
#include "AssetManager.hpp"
#include <iostream>
#include <cmath>

namespace Component
{
    RenderSystem::RenderSystem()
    {
        AddDependency<Transform>();
        AddDependency<Renderer>();
    }

    void RenderSystem::Update(double, ECS::Entity& entity)
    {
        std::unique_ptr<AssetManager> &assetManagerRef = AssetManager::GetInstance();
        Transform& transform = entity.GetComponent<Transform>();
        Renderer& renderer = entity.GetComponent<Renderer>();

        RayLib::Model& model = assetManagerRef->getAssetFromName(renderer.getName()).getModel();

        float rotation = 0.0f;
        RayLib::Vector3 worldUp = RayLib::Vector3();

        if (abs(transform.rotation.x) > abs(transform.rotation.y) && abs(transform.rotation.x) > abs(transform.rotation.z)) {
            worldUp.x = 1.0f;
            rotation = transform.rotation.x;
        }
        if (abs(transform.rotation.y) > abs(transform.rotation.x) && abs(transform.rotation.y) > abs(transform.rotation.z)) {
            worldUp.y = 1.0f;
            rotation = transform.rotation.y;
        }
        if (abs(transform.rotation.z) > abs(transform.rotation.x) && abs(transform.rotation.z) > abs(transform.rotation.y)) {
            worldUp.z = 1.0f;
            rotation = transform.rotation.z;
        }

        model.DrawEx(transform.position, worldUp, rotation, transform.scale, WHITE);

        if (entity.HasComponent<Animator>()) {
            Animator& animator = entity.GetComponent<Animator>();
            animator.PlayCurrentState(model);
        }
    }
}
