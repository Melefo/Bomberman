/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RenderSystem
*/

#ifndef RENDERSYSTEM_HPP_
#define RENDERSYSTEM_HPP_

#include "ASystem.hpp"
#include "Entity.hpp"
#include "Renderer.hpp"

namespace Component
{
    /**
     * @brief Renderer system
     * 
     */
    class RenderSystem : public ECS::ASystem {
        public:
            /**
             * @brief Construct a new Render System object
             * 
             */
            RenderSystem();
            /**
             * @brief Destroy the Render System object
             * 
             */
            ~RenderSystem() override = default;
            /**
             * @brief Construct a new Render System object
             * 
             * @param other 
             */
            RenderSystem(const RenderSystem& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return RenderSystem& 
             */
            RenderSystem& operator=(const RenderSystem& other) = default;

            /**
             * @brief Draw the renderer model to the screen
             * 
             * @param dt 
             * @param entity 
             */
            void Update(double dt, ECS::Entity &entity) override;

        protected:
        private:
    };
}

#endif /* !RENDERSYSTEM_HPP_ */
