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

        if (playerNbr == 1)
            _offset = RayLib::Vector3(100, windowSize.y - 200);
        else if (playerNbr == 2)
            _offset = RayLib::Vector3(windowSize.x - 400, windowSize.y - 200);
        else if (playerNbr == 3)
            _offset = RayLib::Vector3(100, 100);
        else if (playerNbr == 4)
            _offset = RayLib::Vector3(windowSize.x - 400, 100);
        else if (playerNbr == 5)
            _offset = RayLib::Vector3(100, windowSize.y / 2 - 100);
        else if (playerNbr == 6)
            _offset = RayLib::Vector3(windowSize.x - 400, windowSize.y / 2 - 100);
        else if (playerNbr == 7)
            _offset = RayLib::Vector3(windowSize.x / 2 - 200, 100);
        else if (playerNbr == 8)
            _offset = RayLib::Vector3(windowSize.x / 2 - 200, windowSize.y - 200);
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
