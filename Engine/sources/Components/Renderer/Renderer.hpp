/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "IComponent.hpp"
#include "Model.hpp"
#include "Texture.hpp"

namespace Component
{
    /**
     * @brief Renderer component
     * 
     */
    class Renderer : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Renderer object
             * 
             * @param modelPath 
             * @param texturePath 
             */
            Renderer(const std::string& modelPath,
                    const std::string& texturePath);
            /**
             * @brief Construct a new Renderer object
             * 
             * @param modelPath 
             */
            Renderer(const std::string& modelPath);
            /**
             * @brief Construct a new Renderer object (cube mesh)
             * 
             */
            Renderer();
            /**
             * @brief Destroy the Renderer object
             * 
             */
            ~Renderer() override = default;
            /**
             * @brief Construct a new Renderer object
             * 
             * @param other 
             */
            Renderer(const Renderer& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return Renderer 
             */
            Renderer& operator=(const Renderer& other) = default;

            /**
             * @brief Get the Model as a raylib structure 
             * 
             * @return RayLib::Model& 
             */
            RayLib::Model& GetModel(void);

            std::ostream& operator<<(std::ostream& stream) override;

        protected:
        private:
            RayLib::Model _model;
            RayLib::Texture _texture;
    };
}

#endif /* !RENDERER_HPP_ */
