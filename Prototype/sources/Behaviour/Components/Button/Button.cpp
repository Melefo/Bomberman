/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Button
*/

#include "Button.hpp"

namespace Prototype
{
    Button::Button(RayLib::Camera3D& camera, const std::string& texturePath) : IUIObject(), _camera(camera), _texture(texturePath)
    {

    }

    void Button::Draw(RayLib::Vector2<float> position, float scale)
    {
        RayLib::Vector3 vec3Pos = RayLib::Vector3(position.x, position.y, 0.0f);

        _texture.DrawBillboard(_camera, vec3Pos, scale, WHITE);
    }
}

