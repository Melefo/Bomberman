/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** TerrainShader
*/

#ifndef TERRAINSHADER_HPP_
#define TERRAINSHADER_HPP_

#include "Shader.hpp"
#include "Vector2.hpp"

class TerrainShader : public RayLib::Shader {
    public:
        TerrainShader(const std::string& ShaderPath, RayLib::Vector2<float> mapSize);
        ~TerrainShader() = default;

    protected:
    private:
};

#endif /* !TERRAINSHADER_HPP_ */
