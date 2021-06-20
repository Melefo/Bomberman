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
     : _myAController(attatchedController), _offset(GetOffsetFromPlayerNbr(playerNbr))
    {
    }

    RayLib::Vector3 HUD::GetOffsetFromPlayerNbr(int playerNbr)
    {
        std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(0, "");
        RayLib::Vector2<float> scale = window->GetScale();
        RayLib::Vector2<int> size = window->GetSize();

        std::map<int, RayLib::Vector3> hudPos = {
            {1, {0.05f, 0.85f}},
            {2, {0.85f, 0.85f}},
            {3, {0.05f, 0.05f}},
            {4, {0.85f, 0.05f}},
            {5, {0.05f, 0.45f}},
            {6, {0.85f, 0.45f}},
            {7, {0.45f, 0.05f}},
            {8, {0.45f, 0.85f}},
        };

        return (hudPos[playerNbr]);
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
