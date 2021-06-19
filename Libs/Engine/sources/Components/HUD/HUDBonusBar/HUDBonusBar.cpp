/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** HUDBonusBar
*/

#include "HUDBonusBar.hpp"

namespace Component
{
    HUDBonusBar::HUDBonusBar(Component::AController &attatchedController, int playerNbr, float &timer, bool isBg, const std::string &tag)
        : HUD(attatchedController, playerNbr), _timer(timer), _maxTimer(timer), _entityTag(tag), _isBg(isBg)
    {
    }

    HUDBonusBar::~HUDBonusBar()
    {
    }

    void HUDBonusBar::Update(double, ECS::Entity& entity)
    {
        if (!_isBg && _timer > 0.0)
            entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(_timer / _maxTimer > 1? 1.0f: _timer / _maxTimer, 1.0f, 1.0f);
        if (_timer <= 0.0f)
            ECS::Coordinator::GetInstance()->RemoveEntities(_entityTag);
    }

    void HUDBonusBar::FixedUpdate(ECS::Entity&)
    {
    }

    void HUDBonusBar::LateUpdate(double, ECS::Entity&)
    {
    }
}
