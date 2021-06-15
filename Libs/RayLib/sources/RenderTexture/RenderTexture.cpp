/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RenderTexture
*/

#include "RenderTexture.hpp"

namespace RayLib {
    RenderTexture::RenderTexture(int width, int height)
        : _texture(::LoadRenderTexture(width, height))
    {
    }

    RenderTexture::~RenderTexture()
    {
        Unload();
    }

    void RenderTexture::Unload()
    {
        ::UnloadRenderTexture(_texture);
    }

    void RenderTexture::BeginMode() {
        ::BeginTextureMode(_texture);
    }

    void RenderTexture::EndMode()
    {
        ::EndTextureMode();
    }

    void RenderTexture::DrawTexture() {
        ::DrawTextureRec(_texture.texture, {0, 0, static_cast<float>(_texture.texture.width), static_cast<float>(-_texture.texture.height)}, {0, 0}, ::WHITE);
    }

    ::RenderTexture2D& RenderTexture::GetTexture()
    {
        return _texture;
    }
}