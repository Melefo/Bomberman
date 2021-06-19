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
    Texture::Texture(const std::string& filename) : _texture(LoadTexture(filename.c_str())), _fileName(filename)
    {

    }

    Texture::Texture(Image image) : _texture(LoadTextureFromImage(image.GetImage())), _fileName("")
    {

    }

    void Texture::DrawTexture(Vector2<float> position, Color tint)
    {
        ::DrawTextureV(_texture, position.getVector2(), tint.getColor());
    }

    void Texture::DrawTextureEx(Vector2<float> position, float rotation, float scale, Color tint)
    {
        ::DrawTextureEx(_texture, position.getVector2(), rotation, scale, tint.getColor());
    }

    void Texture::DrawTextureRec(RayLib::Rectangle source, RayLib::Vector2<float> position, RayLib::Color col)
    {
        ::DrawTextureRec(_texture, source.GetRectangle(), position.getVector2(), col.getColor());
    }

    void Texture::DrawBillboard(RayLib::Camera3D camera, RayLib::Vector3 center, float size, Color tint)
    {
        ::DrawBillboard(camera.GetCamera(), _texture, center.getVector3(), size, tint.getColor());
    }

    void Texture::DrawTextureNPatch(Vector2<float> position, float rotation, Vector2<float> scale, Color tint)
    {
        Rectangle source(0.0f, 0.0f, static_cast<float>(_texture.width), static_cast<float>(_texture.height));
        NPatchInfo info = {source.GetRectangle(), 0, 0, 0, 0, NPATCH_NINE_PATCH};
        Rectangle dest(position.x, position.y, _texture.width * scale.x, _texture.height * scale.y);
        Vector2 vect(0, 0);

        ::DrawTextureNPatch(_texture, info, dest.GetRectangle(), vect.getVector2(), rotation, tint);
    }

    ::Texture2D Texture::GetTexture()
    {
        return (_texture);
    }

    Texture::~Texture()
    {
        UnloadTexture(_texture);
    }

    const std::string& Texture::GetFileName() const
    {
        return (_fileName);
    }
}