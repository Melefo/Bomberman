/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** UISystem
*/

#ifndef UISYSTEM_HPP_
#define UISYSTEM_HPP_

#include "ASystem.hpp"
#include "Entity.hpp"
#include "Camera3D.hpp"
#include "IUIObject.hpp"
#include "Renderer.hpp"
#include "AssetManager.hpp"
#include "Window.hpp"
#include "GameConfiguration.hpp"

namespace Component
{
    /**
     * @brief UI System
     * 
     */
    class UISystem : public ECS::ASystem {
        public:
            /**
             * @brief Construct a new UISystem object
             * 
             * @param camera 
             */
            UISystem(RayLib::Camera3D& camera);
            /**
             * @brief Destroy the UISystem object
             * 
             */
            ~UISystem() override = default;
            /**
             * @brief Construct a new UISystem object
             * 
             * @param other 
             */
            UISystem(const UISystem& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return UISystem& 
             */
            UISystem& operator=(const UISystem& other) = default;

            /**
             * @brief Call UI object draw function
             * 
             * @param dt 
             * @param entity 
             */
            void Update(double dt, ECS::Entity &entity) override;

        protected:
        private:
            /**
             * @brief Required to temporarily shift from 3D to 2D mode
             * 
             */
            RayLib::Camera3D& _camera;

            std::unique_ptr<RayLib::Window>& _window;

    };
}

#endif /* !UISYSTEM_HPP_ */
