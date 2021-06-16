/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AmbientShader
*/

#ifndef AMBIENTSHADER_HPP_
#define AMBIENTSHADER_HPP_

#include "Shader.hpp"
#include "Color.hpp"

class AmbientShader : public RayLib::Shader {
    public:
        /**
         * @brief Construct a new Ambient Shader object
         * 
         * @param color 
         * @param ShaderPath Path to Shader folder
         */
        AmbientShader(RayLib::Color& color, const std::string& ShaderPath);
        /**
         * @brief Destroy the Ambient Shader object
         * 
         */
        ~AmbientShader() = default;

};

#endif /* !AMBIENTSHADER_HPP_ */
