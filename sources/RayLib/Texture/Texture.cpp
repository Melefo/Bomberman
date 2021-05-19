/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Texture
*/

#include "Texture.hpp"

namespace RayLib
{
    Texture::Texture(const std::string& filename)
    {
        texture = LoadTexture(filename.c_str());
    }

    Texture::Texture(const Image& image)
    {
        texture = LoadTextureFromImage(image.image);
    }

    void Texture::DrawTexture(Vector2<float> position, Color tint)
    {
        ::DrawTextureV(texture, position.getVector2(), tint.getColor());
    }

    void Texture::DrawTextureEx(Vector2<float> position, float rotation, float scale, Color tint)
    {
        ::DrawTextureEx(texture, position.getVector2(), rotation, scale, tint.getColor());
    }

    Texture::~Texture()
    {
        UnloadTexture(texture);
    }
}