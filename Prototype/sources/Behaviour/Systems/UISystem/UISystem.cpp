/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** UISystem
*/

#include "UISystem.hpp"
#include "IUIObject.hpp"
#include "Transform.hpp"
#include <iostream>

namespace Prototype
{
    UISystem::UISystem(RayLib::Camera3D& camera) : _camera(camera)
    {
        AddDependency<IUIObject>();
        AddDependency<Transform>();
    }

    void UISystem::Update(double dt, ECS::Entity& entity)
    {
        (void) dt;
        std::vector<std::reference_wrapper<IUIObject>> uiObjects = entity.OfType<IUIObject>();
        Transform& transform = entity.GetComponent<Transform>();

        RayLib::Vector2<float> position = RayLib::Vector2<float>(transform.position.x, transform.position.y);

        _camera.EndMode();
        for (IUIObject& uiObject : uiObjects) {
            // ! ajouter dans vector3 un .magnitude pour récup un float
            uiObject.Draw(position, RayLib::Vector2<float>(transform.scale.x, transform.scale.y));
        }
        _camera.BeginMode();
    }
}

