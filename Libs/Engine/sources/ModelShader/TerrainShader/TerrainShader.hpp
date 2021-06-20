/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** TerrainShader
*/

#ifndef TERRAINSHADER_HPP_
#define TERRAINSHADER_HPP_

#include "ModelShader.hpp"
#include "Vector2.hpp"

class TerrainShader : public Component::ModelShader {
    public:
        TerrainShader(const std::string& shaderFolderPath, RayLib::Vector2<float> mapSize);
        ~TerrainShader() = default;

        void Update();

    protected:
    private:
};

#endif /* !TERRAINSHADER_HPP_ */
