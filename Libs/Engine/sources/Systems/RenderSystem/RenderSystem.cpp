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
#include "IUIObject.hpp"

namespace Component
{
    RenderSystem::RenderSystem()
    {
        AddDependency<Transform>();
        AddDependency<Renderer>();
        // !get asset manager here ?
    }

    void RenderSystem::Update(double, ECS::Entity& entity)
    {
        std::unique_ptr<AssetManager> &assetManagerRef = AssetManager::GetInstance();
        Transform& transform = entity.GetComponent<Transform>();
        Renderer& renderer = entity.GetComponent<Renderer>();

        //! on ne render pas ici les UI, pour le moment...
        if (entity.OfType<IUIObject>().size() > 0)
            return;

        RayLib::Model& model = assetManagerRef->getAssetFromName(renderer.getName(), entity.GetId()).getModel();

        model.RotateModel(transform.rotation);
        model.DrawEx(transform.position, RayLib::Vector3(0.0f, 0.0f, 0.0f), 0.0f, transform.scale, WHITE);

        if (entity.HasComponent<Animator>()) {
            Animator& animator = entity.GetComponent<Animator>();
            animator.PlayCurrentState(model);
        }
    }
}
