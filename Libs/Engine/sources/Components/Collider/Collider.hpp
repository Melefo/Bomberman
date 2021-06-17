/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Collider
*/

#ifndef COLLIDER_HPP_
#define COLLIDER_HPP_

#include <cinttypes>
#include "IComponent.hpp"
#include "Vector3.hpp"
#include <vector>
#include <memory>
#include "Entity.hpp"
#include "Coordinator.hpp"
#include "BoundingBox.hpp"
#include "RayCollision.hpp"
#include "Ray.hpp"
#include <physac.h>
#include "PhysicsBody.hpp"

namespace Component
{
    /**
     * @brief Collider base component class
     * 
     */
    class Collider : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Collider object
             * 
             * @param attatchedEntity
             */
            Collider(ECS::Entity& attatchedEntity, std::vector<std::string> collisionMask);
            /**
             * @brief Destroy the Collider object
             * 
             */
            ~Collider() = default;
            /**
             * @brief Construct a new Collider object
             * 
             * @param other 
             */
            Collider(const Collider& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return Collider& 
             */
            Collider& operator=(const Collider& other) = default;

            /**
             * @brief Returns true if the collider collides with any other entity
             * 
             * @return true 
             * @return false 
             */
            bool IsColliding(std::vector<std::string> colMask);
            /**
             * @brief Call IsColliding with a temporary position
             * 
             * @param center 
             * @return true 
             * @return false 
             */
            bool IsCollidingAtPosition(RayLib::Vector3 center, std::vector<std::string> colMask);

            /**
             * @brief Returns true if the collider collides with given box
             * 
             * @param box 
             * @return true 
             * @return false 
             */
            bool CheckCollision(RayLib::PhysicsBody& other);

            /**
             * @brief Draw the lines of the collider
             * 
             */
            void DrawLines();

            /**
             * @brief Get the Entity we are colliding with, throws an error if no entity collides
             * 
             * @return ECS::Entity& 
             */
            ECS::Entity& GetCollision(std::vector<std::string> colMask);

            /**
             * @brief Get the Collision Position object
             * 
             * @param center 
             * @return ECS::Entity& 
             */
            ECS::Entity& GetCollisionPosition(RayLib::Vector3 center, std::vector<std::string> colMask);

        protected:
            /**
             * @brief List of the other entities retrieved from the coordinator
             * 
             */
            const std::list<std::unique_ptr<ECS::Entity>>& _otherEntities;
            /**
             * @brief Reference to attatched entity
             * 
             */
            ECS::Entity& _myEntity;

            std::vector<std::string> _collisionMask;
        private:

    };
}

#endif /* !COLLIDER_HPP_ */
