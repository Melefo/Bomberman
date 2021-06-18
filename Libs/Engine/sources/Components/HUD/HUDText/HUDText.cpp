/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** HUDText
*/

#include "HUDText.hpp"

namespace Component {

    HUDText::HUDText(Component::AController &attatchedController, int playerNbr)
        : HUD(attatchedController, playerNbr)
    {
    }

    HUDText::~HUDText()
    {
    }

    void HUDText::Update(double, ECS::Entity&)
    {
    }

    void HUDText::FixedUpdate(ECS::Entity&)
    {
    }

    void HUDText::LateUpdate(double, ECS::Entity&)
    {
    }
}
