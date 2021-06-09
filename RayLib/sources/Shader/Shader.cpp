/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Shader
*/

#include "Shader.hpp"

namespace RayLib
{
    Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        _shader = ::LoadShader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    }

    Shader::~Shader()
    {
        ::UnloadShader(_shader);
    }

    int Shader::GetLocation(std::string location)
    {
        return ::GetShaderLocation(_shader, location.c_str());
    }

    void Shader::Unload()
    {
        ::UnloadShader(_shader);
    }

    void Shader::BeginMode()
    {
        ::BeginShaderMode(_shader);
    };

    void Shader::EndMode()
    {
        ::EndShaderMode();
    };

};