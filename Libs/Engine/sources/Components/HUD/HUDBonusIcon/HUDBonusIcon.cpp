/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** HUDBonusIcon
*/

#include "HUDBonusIcon.hpp"

namespace Component
{
    HUDBonusIcon::HUDBonusIcon(Component::AController &attatchedController, int playerNbr, float &timer)
        : HUD(attatchedController, playerNbr), _timer(timer), _entityTag("HUD_")
    {
        if (playerNbr <= 9)
            _entityTag += "00" + std::to_string(playerNbr);
        else if (playerNbr <= 99)
            _entityTag += "0" + std::to_string(playerNbr);
        else if (playerNbr <= 999)
            _entityTag += "" + std::to_string(playerNbr);
        _entityTag += "_bonusIcon";
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
