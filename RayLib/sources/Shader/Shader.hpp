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
            Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
            Shader(Shader& shader);
            Shader(::Shader& shader);
            ~Shader();

            ::Shader& GetShader();

            int GetLocation(std::string location);

            template <typename T>
            void SetValue(int location, T value, int uniformType)
            {
                ::SetShaderValue(_shader, location, static_cast<void *>(&value), uniformType);
            }

            void SetLoc(int locId, std::string location)
            {
                _shader.locs[locId] = GetLocation(location);
            }

            void Unload();
            void BeginMode();
            void EndMode();

        protected:
        private:
            ::Shader _shader;
    };
};

#endif /* !SHADER_HPP_ */
