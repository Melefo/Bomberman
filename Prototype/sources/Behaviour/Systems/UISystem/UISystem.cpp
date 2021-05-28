/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** UISystem
*/

#include "UISystem.hpp"
#include "IUIObject.hpp"
#include "Transform.hpp"

namespace Prototype
{
    UISystem::UISystem()
    {
        AddDependency<IUIObject>();
        AddDependency<Transform>();
    }

    void UISystem::Update(double dt, ECS::Entity& entity)
    {
        IUIObject& uiObject = entity.GetComponent<IUIObject>();
        Transform& transform = entity.GetComponent<Transform>();

        RayLib::Vector2<float> position = RayLib::Vector2<float>(transform.position.x, transform.position.y);
        // ! ajouter dans vector3 un .magnitude pour récup un float
        uiObject.Draw(position, transform.scale.x);
    }
}

