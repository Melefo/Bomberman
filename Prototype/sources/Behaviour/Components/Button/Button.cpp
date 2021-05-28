/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Button
*/

#include "Button.hpp"

namespace Prototype
{
    Button::Button(const std::string& texturePath) : IUIObject(), _texture(texturePath)
    {

    }

    void Button::Draw(RayLib::Vector2<float> position, float scale)
    {
        _texture.DrawTextureEx(position, 0.0f, scale, WHITE);
    }
}

