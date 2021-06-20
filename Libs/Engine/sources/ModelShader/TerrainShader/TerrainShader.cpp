/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** TerrainShader
*/

#include "TerrainShader.hpp"
#include "AssetCache.hpp"
#include "Shader.hpp"

TerrainShader::TerrainShader(const std::string& shaderFolderPath, RayLib::Vector2<float> mapSize)
    : Component::ModelShader(shaderFolderPath)
{
    std::shared_ptr<RayLib::Shader> shader = AssetCache::GetAsset<RayLib::Shader>(shaderFolderPath);
    shader->SetValue(shader->GetLocation("mapSize"), mapSize.getVector2(), SHADER_UNIFORM_VEC2);
}

void TerrainShader::Update()
{
}
