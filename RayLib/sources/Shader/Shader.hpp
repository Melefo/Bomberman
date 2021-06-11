/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Shader
*/

#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <string>
#include <raylib.h>
#include <vector>

namespace RayLib
{
    /**
     * @brief Shader
     * Encapsulation of the raylib structure Shader
     */
    class Shader {
        public:
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
            ~Shader();

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
             * @brief Set a value to an element of a shader file
             * 
             * @tparam T Any value between
             * FLOAT
             * VEC2
             * VEC3
             * VEC4
             * INT
             * IVEC2
             * IVEC3
             * IVEC4
             * SAMPLER2D
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
            template <typename T>
            void SetValue(int location, T value, int uniformType)
            {
                ::SetShaderValue(_shader, location, static_cast<void *>(&value), uniformType);
            }

            /**
             * @brief Set a new location into the shader locs array
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
        private:
            /**
             * @brief The C raylib's Shader structure
             * 
             */
            ::Shader _shader;
    };
};

#endif /* !SHADER_HPP_ */
