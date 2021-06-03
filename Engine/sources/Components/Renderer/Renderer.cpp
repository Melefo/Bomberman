/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Renderer
*/

#include "Renderer.hpp"

namespace Component
{

    Renderer::Renderer(const std::string& modelPath) :
    _model(modelPath), _texture()
    {
        _model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, _texture);
    }

    Renderer::Renderer() :
    _model(RayLib::Mesh(RayLib::Vector3(1.0f, 1.0f, 1.0f))), _texture("../assets/models/cube/def_text.png")
    {
        _model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, _texture);
    }

    Renderer::Renderer(const std::string& modelPath, const std::string& texturePath) :
    _model(modelPath), _texture(texturePath)
    {
        _model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, _texture);
    }


    RayLib::Model& Renderer::GetModel()
    {
        return (_model);
    }
}
