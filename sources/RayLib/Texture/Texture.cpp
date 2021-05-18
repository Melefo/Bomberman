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

    void Texture::DrawTexture(Vector2 position, Color tint)
    {
        ::DrawTextureV(texture, {position.x, position.y}, {tint.r, tint.g, tint.b, tint.a});
    }

    void Texture::DrawTextureEx(Vector2 position, float rotation, float scale, Color tint)
    {
        ::DrawTextureEx(texture, {position.x, position.y}, rotation, scale, {tint.r, tint.g, tint.b, tint.a});
    }

    Texture::~Texture()
    {
        UnloadTexture(texture);
    }
}