/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PauseSystem
*/

#ifndef PAUSESYSTEM_HPP_
#define PAUSESYSTEM_HPP_

#include "ASystem.hpp"
#include "Entity.hpp"
#include "Renderer.hpp"
#include "Animator.hpp"
#include "Input.hpp"
#include "Coordinator.hpp"
#include "BehaviourSystem.hpp"
#include "PhysicsSystem.hpp"
#include "EntityFactory.hpp"
#include "ButtonCallbacks.hpp"
#include "Button.hpp"

namespace Component
{
    class PauseSystem : public ECS::ASystem {
        public:
            /**
             * @brief Construct a new Pause System object
             * 
             */
            PauseSystem();
            /**
             * @brief Destroy the Pause System object
             * 
             */
            ~PauseSystem() override = default;
            /**
             * @brief Construct a new Pause System object
             * 
             * @param other 
             */
            PauseSystem(const PauseSystem& other) = default;
            /**
             * @brief Assignement operator
             * 
             * @param other 
             * @return PauseSystem& 
             */
            PauseSystem& operator=(const PauseSystem& other) = default;

            void Update(double dt, ECS::Entity &entity) override;
            void FixedUpdate(ECS::Entity &entity) override;
            void LateUpdate(double dt, ECS::Entity &entity) override;
        protected:
        private:
            /**
             * @brief input
             * 
             */
            RayLib::Input _input;
    };
}

#endif /* !PAUSESYSTEM_HPP_ */
