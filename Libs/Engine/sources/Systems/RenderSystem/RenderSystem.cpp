/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"
#include "Transform.hpp"
#include <iostream>
#include <cmath>
#include "IUIObject.hpp"
#include "Drawable3D.hpp"
#include "ModelShader.hpp"

namespace Component
{
    RenderSystem::RenderSystem()
    {
        AddDependency<Transform>();
        //AddDependency<Renderer>();
        AddDependency<Drawable3D>();

        // !get asset manager here ?
    }

    void RenderSystem::Update(double, ECS::Entity&entity)
    {
        if (entity.OfType<IUIObject>().size() > 0)
            return;
        Transform& transform = entity.GetComponent<Transform>();
        Drawable3D& drawable = entity.GetComponent<Drawable3D>();

        drawable.RotateModel(transform.rotation);

        if (entity.HasComponent<Animator>()) {
            Animator& animator = entity.GetComponent<Animator>();
            animator.PlayCurrentState(drawable.GetModel());
        }
        if (entity.HasComponent<ModelShader>()) {
            ModelShader& modelShader = entity.GetComponent<ModelShader>();
            modelShader.Update();
        }

        drawable.Draw(transform.position, transform.scale, WHITE);
    }

    void RenderSystem::FixedUpdate(ECS::Entity &)
    {
    }
}
