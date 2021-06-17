/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** UISystem
*/

#include "UISystem.hpp"
#include "Transform.hpp"
#include <iostream>

namespace Component
{
    UISystem::UISystem(RayLib::Camera3D& camera) : _camera(camera), _window(RayLib::Window::GetInstance(0.0f, ""))
    {
        // ! obsolète ?
        AddDependency<IUIObject>();

        AddDependency<Transform>();
    }

    void UISystem::Update(double, ECS::Entity& entity)
    {
        Transform& transform = entity.GetComponent<Transform>();

        std::vector<std::reference_wrapper<IUIObject>> uiObjects = entity.OfType<IUIObject>();
        RayLib::Vector2<float> position = RayLib::Vector2<float>(transform.position.x, transform.position.y);
        RayLib::Vector2<float> scale = RayLib::Vector2<float>(transform.scale.x, transform.scale.y);


        _camera.EndMode();
        for (IUIObject& uiObject : uiObjects) {
            uiObject.Draw(position, scale);
        }

        if (Engine::GameConfiguration::GetDebugMode())
            _window->DrawFPS(RayLib::Vector2<int>(10, 10));
        _camera.BeginMode();
    }
}
