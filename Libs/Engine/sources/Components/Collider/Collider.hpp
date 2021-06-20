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
#include "Transform.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"

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
             * @brief Check if the entity collide with another
             * 
             * @return true 
             * @return false 
             */
            virtual bool IsColliding(void) = 0;

            /**
             * @brief Check if the entity collide at a specific position
             * 
             * @param pos 
             * @return true 
             * @return false 
             */
            virtual bool IsCollidingAtPosition(RayLib::Vector2<float> pos) = 0;

            /**
             * @brief Check a circle collision
             * 
             * @param circle 
             * @return true 
             * @return false 
             */
            virtual bool CheckCollision(RayLib::Circle& circle) = 0;
            /**
             * @brief Check a rectangle collision
             * 
             * @param rec 
             * @return true 
             * @return false 
             */
            virtual bool CheckCollision(RayLib::Rectangle& rec) = 0;

            /**
             * @brief Draw collision lines
             * 
             */
            virtual void DrawLines() = 0;

            /**
             * @brief Get the Collision object
             * 
             * @return ECS::Entity& 
             */
            virtual ECS::Entity& GetCollision(void) = 0;
            /**
             * @brief Get the Collision Position object
             * 
             * @param pos 
             * @return ECS::Entity& 
             */
            virtual ECS::Entity& GetCollisionPosition(RayLib::Vector2<float> pos) = 0;

            // virtual RayLib::PhysacBody& GetPhysacBody() = 0;

            // ! change collision mask at runtime ??

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
