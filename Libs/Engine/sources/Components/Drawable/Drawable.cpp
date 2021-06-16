/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Drawable
*/

#include "Drawable.hpp"

namespace Component
{
    Drawable::Drawable(RayLib::Mesh& mesh) : _model(mesh)
    {
    }

    Drawable::Drawable(const std::string& path) : _model(path)
    {
        // ! check if the asset manager has model cached
        // ? shared_ptr
    }

    void Drawable::Draw(RayLib::Vector3 position, RayLib::Vector3 rotationAxis, float rotationAngle, RayLib::Vector3 scale, RayLib::Color tint)
    {
        _model.DrawEx(position, rotationAxis, rotationAngle, scale, tint);
    }

    void Drawable::SetMaterialTexture(int matIndex, int mapType, RayLib::Texture& text)
    {
        _model.SetMaterialTexture(matIndex, mapType, text);
    }

    void Drawable::SetMaterialShader(int matIndex, RayLib::Shader& shader)
    {
        _model.SetMaterialShader(matIndex, shader);
    }

}
