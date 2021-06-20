/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Light
*/

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include "Vector3.hpp"
#include "Color.hpp"
#include "Shader.hpp"

class BasicLight : public RayLib::Shader {
    public:
        // Light type
        enum class LightType {
            LIGHT_DIRECTIONAL,
            LIGHT_POINT
        };

        /**
         * @brief Construct a new Basic Light object and get linked shader locations
         * 
         * @param type 
         * @param position 
         * @param color 
         * @param ShaderPath 
         */
        BasicLight(LightType type, RayLib::Vector3 position, RayLib::Color& color, const std::string& ShaderPath);
        /**
         * @brief Destroy the BasicLight object
         * 
         */
        ~BasicLight() = default;

        /**
         * @brief Update shader's light properties
         *
         */
        void UpdateValues();

        /**
         * @brief Get light source position
         * 
         * @return ::Vector3& 
         */
        ::Vector3& GetPosition();

    protected:
    private:
        int _type;
        ::Vector3 _position;
        ::Vector3 _target;
        ::Color _color;
        // Shader locations
        int _typeLoc;
        int _posLoc;
        int _targetLoc;
        int _colorLoc;
};

#endif /* !LIGHT_HPP_ */
