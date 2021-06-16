/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AmbientShader
*/

#include "AmbientShader.hpp"
#include "Vector4.hpp"
#include <iostream>

AmbientShader::AmbientShader(RayLib::Color& color, const std::string& ShaderPath)
    : RayLib::Shader("", ShaderPath+"ambient_lighting.fs")
{
    int location = GetLocation("color");
    RayLib::Vector4 shaderColor(color.r/static_cast<float>(255),
        color.g/static_cast<float>(255),
        color.b/static_cast<float>(255),
        color.a/static_cast<float>(255));

    SetValue(location, shaderColor.getVector4(), SHADER_UNIFORM_VEC4);
}
