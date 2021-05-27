/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Renderer
*/

#include "Renderer.hpp"

Renderer::Renderer(const std::string& modelPath, const std::string& texturePath) :
_model(modelPath), _texture(texturePath)
{
    _model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, _texture);
}


RayLib::Model& Renderer::GetModel()
{
    return (_model);
}

