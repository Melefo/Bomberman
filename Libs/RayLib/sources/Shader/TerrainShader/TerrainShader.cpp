/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** TerrainShader
*/

#include "TerrainShader.hpp"

TerrainShader::TerrainShader(const std::string& ShaderPath, RayLib::Vector2<float> mapSize)
    : RayLib::Shader("", ShaderPath+"terrainShader.fs")
{
    SetValue(GetLocation("mapSize"), mapSize.getVector2(), SHADER_UNIFORM_VEC2);
}
