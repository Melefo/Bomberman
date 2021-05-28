/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Texture
*/

#include "Texture.hpp"
#include <iostream>

namespace RayLib
{
    Texture::Texture(const std::string& filename)
    {
        _texture = LoadTexture(filename.c_str());
    }

    Texture::Texture(const Image& image)
    {
        _texture = LoadTextureFromImage(image.image);
    }

    void Texture::DrawTexture(Vector2<float> position, Color tint)
    {
        ::DrawTextureV(_texture, position.getVector2(), tint.getColor());
    }

    void Texture::DrawTextureEx(Vector2<float> position, float rotation, float scale, Color tint)
    {
        ::DrawTextureEx(_texture, position.getVector2(), rotation, scale, tint.getColor());
    }

    ::Texture2D Texture::GetTexture()
    {
        return (_texture);
    }

    Texture::~Texture()
    {
        std::cout << "Unloading texture" << std::endl;
        UnloadTexture(_texture);
    }
}