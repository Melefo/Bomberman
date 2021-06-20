/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** HUDBonusIcon
*/

#include "HUDBonusIcon.hpp"

namespace Component
{
    HUDBonusIcon::HUDBonusIcon(Component::AController &attatchedController, int playerNbr, float &timer, const std::string &tag)
        : HUD(attatchedController, playerNbr), _timer(timer), _entityTag(tag)
    {
    }

    HUDBonusIcon::~HUDBonusIcon()
    {
    }

    void HUDBonusIcon::Update(double, ECS::Entity&)
    {
        if (_timer <= 0.0f)
            ECS::Coordinator::GetInstance()->RemoveEntities(_entityTag);
    }

    void HUDBonusIcon::FixedUpdate(ECS::Entity&)
    {
    }

    void HUDBonusIcon::LateUpdate(double, ECS::Entity&)
    {
    }
}
