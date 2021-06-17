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
#include "Drawable3D.hpp"

namespace Component
{
    RenderSystem::RenderSystem()
    {
        AddDependency<Transform>();
        //AddDependency<Renderer>();
        AddDependency<Drawable3D>();

        // !get asset manager here ?
    }

    void RenderSystem::Update(double, ECS::Entity& entity)
    {
        std::unique_ptr<AssetManager> &assetManagerRef = AssetManager::GetInstance();
        Transform& transform = entity.GetComponent<Transform>();
        //Renderer& renderer = entity.GetComponent<Renderer>();
        Drawable3D& drawable = entity.GetComponent<Drawable3D>();

        //! on ne render pas ici les UI, pour le moment...
        if (entity.OfType<IUIObject>().size() > 0)
            return;

        //RayLib::Model& model = assetManagerRef->getAssetFromName(renderer.getName(), entity.GetId()).getModel();

        drawable.RotateModel(transform.rotation);
        drawable.Draw(transform.position, transform.scale, WHITE);
        //model.RotateModel(transform.rotation);
        //model.DrawEx(transform.position, RayLib::Vector3(0.0f, 0.0f, 0.0f), 0.0f, transform.scale, WHITE);

        //if (entity.HasComponent<Animator>()) {
        //    Animator& animator = entity.GetComponent<Animator>();
        //    animator.PlayCurrentState(model);
        //}
    }
}
