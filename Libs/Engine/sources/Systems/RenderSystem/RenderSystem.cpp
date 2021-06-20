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
        if (entity.HasComponent<Animator>())
            return;

        Transform& transform = entity.GetComponent<Transform>();
        entity.GetComponent<Drawable3D>().Draw(transform.position, transform.scale, WHITE);

    }

    void RenderSystem::FixedUpdate(ECS::Entity &entity)
    {
        Transform& transform = entity.GetComponent<Transform>();
        Drawable3D& drawable = entity.GetComponent<Drawable3D>();

        //! on ne render pas ici les UI, pour le moment...
        if (entity.OfType<IUIObject>().size() > 0)
            return;

        drawable.RotateModel(transform.rotation);

        if (entity.HasComponent<Animator>()) {
            Animator& animator = entity.GetComponent<Animator>();
            animator.PlayCurrentState(drawable.GetModel());
        }
        drawable.Draw(transform.position, transform.scale, WHITE);
    }
}
