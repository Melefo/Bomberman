/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** BoxCollider
*/

#ifndef BOXCOLLIDER_HPP_
#define BOXCOLLIDER_HPP_

#include <cinttypes>
#include "IComponent.hpp"
#include "Vector3.hpp"
#include "Collider.hpp"
#include "BoundingBox.hpp"
#include "Physics3D.hpp"

namespace Component
{
    /**
     * @brief Box collider class
     * 
     */
    class BoxCollider : public Collider {
        public:

            /**
             * @brief Construct a new Box Collider
             * 
             * @param attatchedEntity required to update the position (via the transform component)
             * @param scale initial scale of the box
             */
            BoxCollider(ECS::Entity& attatchedEntity,
                        RayLib::Vector3 scale=RayLib::Vector3(1.0f, 1.0f, 1.0f));
            /**
             * @brief Destroy the Box Collider object
             * 
             */
            ~BoxCollider() = default;
            /**
             * @brief Construct a new Box Collider object
             * 
             * @param other 
             */
            BoxCollider(const BoxCollider& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return BoxCollider& 
             */
            BoxCollider& operator=(const BoxCollider& other) = default;

            /**
             * @brief Returns true if the box is colliding with another entity
             * 
             * @return true 
             * @return false 
             */
            bool IsColliding() override;
            /**
             * @brief Returns true if the box is colliding with the circle
             * 
             * @param center 
             * @param radius 
             * @return true 
             * @return false 
             */
            bool CheckCollision(RayLib::Vector3 center, float radius) override;
            /**
             * @brief Returns true if the box is colliding with the given box
             * 
             * @param box 
             * @return true 
             * @return false 
             */
            bool CheckCollision(RayLib::BoundingBox& box) override;

            /**
             * @brief Returns true if the box is colliding with the ray
             * 
             * @param ray 
             * @return true 
             * @return false 
             */
            bool CheckCollision(RayLib::Ray& ray) override;

            /**
             * @brief Returns true if the box is colliding with anything, at given position
             * 
             * @param center a temporary position to check against
             * @return true 
             * @return false 
             */
            bool IsCollidingAtPosition(RayLib::Vector3 center) override;

            /**
             * @brief Use the window singleton to draw the collider's wires
             * 
             */
            void DrawLines() override;

            /**
             * @brief Called to update the collider's position relative to entity transform
             * 
             */
            void UpdateBounds();

            /**
             * @brief Get the entity with which we collide, throws an error if there is none
             * 
             * @return ECS::Entity& 
             */
            ECS::Entity& GetCollision() override;

        protected:
        private:
            /**
             * @brief The box's scale
             * 
             */
            RayLib::Vector3 _scale;
            /**
             * @brief The box's bounds
             * 
             */
            RayLib::BoundingBox _bounds;
    };
}

#endif /* !BOXCOLLIDER_HPP_ */
