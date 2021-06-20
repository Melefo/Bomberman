/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsSystem
*/

#ifndef PHYSICSSYSTEM_HPP_
#define PHYSICSSYSTEM_HPP_

#include "ASystem.hpp"
#include "Entity.hpp"
#include "PhysicsBody.hpp"

namespace Component
{
    class PhysicsSystem : public ECS::ASystem {
        public:
            /**
             * @brief Construct a new Physics System object
             * 
             */
            PhysicsSystem();
            /**
             * @brief Destroy the Physics System object
             * 
             */
            ~PhysicsSystem() override = default;
            /**
             * @brief Construct a new Physics System object
             * 
             * @param other 
             */
            PhysicsSystem(const PhysicsSystem& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return PhysicsSystem& 
             */
            PhysicsSystem& operator=(const PhysicsSystem& other) = default;

            void FixedUpdate(ECS::Entity &entity) override;
            void Update(double dt, ECS::Entity &entity) override;


        protected:
        private:
    };
}

#endif /* !PHYSICSSYSTEM_HPP_ */
