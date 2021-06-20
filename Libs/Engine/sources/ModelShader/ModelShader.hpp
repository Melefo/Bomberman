/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** ModelShader
*/

#ifndef CUSTOMSHADER_HPP_
#define CUSTOMSHADER_HPP_

#include "IComponent.hpp"

namespace Component {
    class ModelShader : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Model Shader object
             * 
             * @param shaderPath 
             */
            ModelShader(const std::string shaderPath);
            /**
             * @brief Destroy the Model Shader object
             * 
             */
            ~ModelShader() = default;
            /**
             * @brief Construct a new Model Shader object
             * 
             * @param other 
             */
            ModelShader(const ModelShader& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return ModelShader& 
             */
            ModelShader& operator=(const ModelShader& other) = default;

            virtual void Update() = 0;

            std::ostream &operator<<(std::ostream &os);
            std::istream &operator>>(std::istream &is);
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree);

        protected:
        private:
    };
}

#endif /* !CUSTOMSHADER_HPP_ */
