/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** HUD
*/

#include "HUD.hpp"

namespace Component
{
    HUD::HUD(Component::AController &attatchedController, int playerNbr)
     : _myAController(attatchedController)
    {
        RayLib::Vector2<int> windowSize = RayLib::Window::GetInstance(0, "")->GetSize();
        std::map<int, RayLib::Vector3> hudPos = {
            {1, {100.0f, windowSize.y - 200.0f}},
            {2, {windowSize.x - 400.0f, windowSize.y - 200.0f}},
            {3, {100.0f, 100.0f}},
            {4, {windowSize.x - 400.0f, 100.0f}},
            {5, {100.0f, windowSize.y / 2.0f - 100.0f}},
            {6, {windowSize.x - 400.0f, windowSize.y / 2.0f - 100.0f}},
            {7, {windowSize.x / 2.0f - 200.0f, 100.0f}},
            {8, {windowSize.x / 2.0f - 200.0f, windowSize.y - 200.0f}},
        };
        _offset = hudPos[playerNbr];
    }

    RayLib::Vector3 &HUD::getOffset()
    {
        return (_offset);
    }

    Component::AController &HUD::getAController()
    {
        return (_myAController);
    }
}
