/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Shader
*/

#ifndef SHADER_HPP_
#define SHADER_HPP_

#include "IAsset.hpp"
#include <string>
#include <raylib.h>
#include <vector>

namespace RayLib
{
    /**
     * @brief Shader
     * Encapsulation of the raylib structure Shader
     */
    class Shader : public IAsset {
        public:
            /**
             * @brief Construct a new Shader object
             * 
             * @param shadersPath The path to the vertex and fragment shader
             */
            Shader(const std::string& shadersPath);
            /**
             * @brief Construct a new Shader object
             * 
             * @param vertexShaderPath Path to a .vs or .vert file (Vertex shader). "" for no file
             * @param fragmentShaderPath Path to a .fs or .frag file (Fragment shader). "" for no file
             */
            Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
            /**
             * @brief Construct a new Shader object
             * 
             * @param shader RayLib::Shader object to copy
             */
            Shader(Shader& shader);
            /**
             * @brief Construct a new Shader object
             * 
             * @param shader ::Shader struct to copy
             */
            Shader(::Shader& shader);
            /**
             * @brief Destroy the Shader object
             * 
             */
            ~Shader() override;

            /**
             * @brief Get the Shader structure
             * 
             * @return ::Shader& The Shader structure
             */
            ::Shader& GetShader();

            /**
             * @brief Get the location of the element in the loaded file
             * 
             * @param location Object to find
             * @return int The location of the element
             */
            int GetLocation(std::string location);

            /**
             * @brief Set the Value to an element of a shader file
             * 
             * @tparam T 
             * @param location The location in the file. Found with GetLocation function
             * @param value The value to set
             * @param uniformType The uniform type of the value
             * Uniform types are:
             * SHADER_UNIFORM_FLOAT
             * SHADER_UNIFORM_VEC2
             * SHADER_UNIFORM_VEC3
             * SHADER_UNIFORM_VEC4
             * SHADER_UNIFORM_INT
             * SHADER_UNIFORM_IVEC2
             * SHADER_UNIFORM_IVEC3
             * SHADER_UNIFORM_IVEC4
             * SHADER_UNIFORM_SAMPLER2D
             */
            template<typename T>
            void SetValue(int location, T value, int uniformType)
            {
                ::SetShaderValue(_shader, location, &value, uniformType);
            }

            /**
             * @brief Set locId raylib attribute new location according to the loaded shader
             * 
             * @param locId Id of the location
             * @param location Name of the location to find
             */
            void SetLoc(int locId, std::string location)
            {
                _shader.locs[locId] = GetLocation(location);
            }

            /**
             * @brief Unload the loaded shader
             * 
             */
            void Unload();
            /**
             * @brief Begin Shader Mode
             * 
             */
            void BeginMode();
            /**
             * @brief End Shader Mode
             * 
             */
            void EndMode();

        protected:
            /**
             * @brief The C raylib's Shader structure
             * 
             */
            ::Shader _shader;
    };
};

#endif /* !SHADER_HPP_ */
