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
            Collider(ECS::Entity& attatchedEntity);
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
            virtual bool IsColliding();
            /**
             * @brief Call IsColliding with a temporary position
             * 
             * @param center 
             * @return true 
             * @return false 
             */
            virtual bool IsCollidingAtPosition(RayLib::Vector3 center) = 0;
            /**
             * @brief Returns true if the collider collides with given circle
             * 
             * @param center 
             * @param radius 
             * @return true 
             * @return false 
             */
            virtual bool CheckCollision(RayLib::Vector3 center, float radius) = 0;
            /**
             * @brief Returns true if the collider collides with given box
             * 
             * @param box 
             * @return true 
             * @return false 
             */
            virtual bool CheckCollision(RayLib::BoundingBox& box) = 0;
            /**
             * @brief Returns true if the collider collides with given ray
             * 
             * @param ray 
             * @return true 
             * @return false 
             */
            virtual bool CheckCollision(RayLib::Ray& ray) = 0;

            /**
             * @brief Draw the lines of the collider
             * 
             */
            virtual void DrawLines() = 0;

            /**
             * @brief Get the Entity we are colliding with, throws an error if no entity collides
             * 
             * @return ECS::Entity& 
             */
            virtual ECS::Entity& GetCollision() = 0;

            virtual std::ostream& operator<<(std::ostream& stream) = 0;

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
        private:

    };
}

#endif /* !COLLIDER_HPP_ */
