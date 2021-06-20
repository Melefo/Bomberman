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
        /**
         * @brief Construct a new Terrain Shader object
         * 
         * @param shaderFolderPath 
         * @param mapSize 
         */
        TerrainShader(const std::string& shaderFolderPath, RayLib::Vector2<float> mapSize);
        /**
         * @brief Destroy the Terrain Shader object
         * 
         */
        ~TerrainShader() = default;
        /**
         * @brief Construct a new Terrain Shader object
         * 
         * @param other 
         */
        TerrainShader(const TerrainShader& other) = default;
        /**
         * @brief Assignment operator
         * 
         * @param other 
         * @return TerrainShader& 
         */
        TerrainShader& operator=(const TerrainShader& other) = default;

        void Update();

    protected:
    private:
};

#endif /* !TERRAINSHADER_HPP_ */
