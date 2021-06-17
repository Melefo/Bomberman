/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Drawable3D
*/

#include "Drawable3D.hpp"
#include "AssetCache.hpp"

namespace Component
{
    Drawable3D::Drawable3D(RayLib::Mesh& mesh) : _model(mesh)
    {
    }

    Drawable3D::Drawable3D(const std::string& path) : _model(AssetCache::GetAsset<RayLib::Mesh>(path))
    {

    }

    void Drawable3D::Draw(RayLib::Vector3 position, RayLib::Vector3 scale, RayLib::Color tint)
    {
        // rotation and angle are taken from the transform
        _model.DrawEx(position, 0.0f, 0.0f, scale, tint);
    }

    void Drawable3D::SetMaterialTexture(int matIndex, int mapType, RayLib::Texture& text)
    {
        _model.SetMaterialTexture(matIndex, mapType, text);
    }

    void Drawable3D::SetMaterialShader(int matIndex, RayLib::Shader& shader)
    {
        _model.SetMaterialShader(matIndex, shader);
    }

    void Drawable3D::RotateModel(RayLib::Vector3 rotation)
    {
        _model.RotateModel(rotation);
    }
}
