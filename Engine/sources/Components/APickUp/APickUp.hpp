/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** APickUp
*/

#ifndef APICKUP_HPP_
#define APICKUP_HPP_

#include "IBehaviour.hpp"
#include "Collider.hpp"
#include "CollisionSystem.hpp"
#include "Transform.hpp"
#include "Window.hpp"

namespace Component
{
    class APickUp : public IBehaviour {
        public:
            /**
             * @brief Construct a new APickUp object
             * 
             * @param entity 
             * @param pickupRadius 
             */
            APickUp(ECS::Entity& entity, float pickupRadius=2.0f);
            /**
             * @brief Destroy the APickUp object
             * 
             */
            ~APickUp() = default;
            /**
             * @brief Construct a new APickUp object
             * 
             * @param other 
             */
            APickUp(const APickUp& other) = default;
            /**
             * @brief Assignement operator
             * 
             * @param other 
             * @return APickUp& 
             */
            APickUp& operator=(const APickUp& other) = default;

            /**
             * @brief Function called when the pickup detects a player or AI in its pickupradius
             * 
             * @param collision 
             */
            virtual void OnPickup(ECS::Entity& collision) = 0;

            /**
             * @brief Called every frame
             * 
             * @param dt 
             * @param entity 
             */
            virtual void Update(double dt, ECS::Entity& entity) = 0;
            /**
             * @brief Check collision, call OnPickup
             * 
             * @param entity 
             */
            void FixedUpdate(ECS::Entity& entity) override;
            /**
             * @brief 
             * 
             * @param dt 
             * @param entity 
             */
            virtual void LateUpdate(double dt, ECS::Entity& entity) = 0;

        protected:
            ECS::Entity& _entity;
            float _pickupRadius;
            ECS::Coordinator& _coordinator;
        private:
    };
}

#endif /* !APICKUP_HPP_ */
