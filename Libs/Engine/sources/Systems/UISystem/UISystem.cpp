/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** UISystem
*/

#include "UISystem.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include <iostream>

namespace Component
{
    UISystem::UISystem() : _window(RayLib::Window::GetInstance(0, ""))
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

        RayLib::Vector2<int> size = this->_window->GetSize();
        RayLib::Vector2<float> windowScale = this->_window->GetScale();
        scale.x *= windowScale.x;
        scale.y *= windowScale.y;
        position.x *= size.x;
        position.y *= size.y;
        try
        {
            RayLib::Camera3D& camera = Component::Camera::GetMainCamera().camera;

            camera.EndMode();
            for (IUIObject& uiObject : uiObjects) {
                uiObject.Draw(position, scale);
            }

            if (Engine::GameConfiguration::GetDebugMode())
                _window->DrawFPS(RayLib::Vector2<int>(10, 10));
            camera.BeginMode();
        }
        catch (ECS::Exception::ComponentException&)
        {
            return;
        }
    }
}
