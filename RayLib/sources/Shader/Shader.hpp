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
#include <unordered_map>

namespace RayLib
{
    /**
     * @brief Shader
     * Encapsulation of the raylib structure Shader
     */
    class Shader {
        public:
            Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
            ~Shader();

            int GetLocation(std::string location);

            template <typename T>
            void SetValue(std::string location, T value, ShaderUniformDataType uniformType)
            {
                if (_locations.find(location) == _locations.end())
                    _locations[location] = GetLocation(location);
                ::SetShaderValue(_shader, _locations[location], static_cast<void *>(&value), uniformType);
            }

            void Unload();
            void BeginMode();
            void EndMode();

        protected:
        private:
            ::Shader _shader;
            std::unordered_map<std::string, int> _locations;
    };
};

#endif /* !SHADER_HPP_ */
