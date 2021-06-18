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
            {1, {100, windowSize.y - 200}},
            {2, {windowSize.x - 400, windowSize.y - 200}},
            {3, {100, 100}},
            {4, {windowSize.x - 400, 100}},
            {5, {100, windowSize.y / 2 - 100}},
            {6, {windowSize.x - 400, windowSize.y / 2 - 100}},
            {7, {windowSize.x / 2 - 200, 100}},
            {8, {windowSize.x / 2 - 200, windowSize.y - 200}},
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
