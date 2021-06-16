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
    float size[2] = {mapSize.x, mapSize.y};

    SetValue(GetLocation("mapSize"), size, SHADER_UNIFORM_VEC2);
}
