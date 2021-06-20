/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** SquareCollider
*/

#ifndef SQUARECOLLIDER_HPP_
#define SQUARECOLLIDER_HPP_

#include <cinttypes>
#include "IComponent.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include <vector>
#include <memory>
#include "Entity.hpp"
#include "Coordinator.hpp"
#include "Transform.hpp"
#include "Collider.hpp"
#include "Rectangle.hpp"
#include "Physics2D.hpp"

namespace Component
{
    class SquareCollider : public Collider {
        public:
            /**
             * @brief Construct a new Square Collider object
             * 
             * @param attatchedEntity 
             * @param collisionMask 
             * @param pos 
             * @param scale 
             */

            SquareCollider(ECS::Entity& attatchedEntity, std::vector<std::string> collisionMask, RayLib::Vector2<float> pos, RayLib::Vector2<float> scale);
            /**
             * @brief Destroy the Square Collider object
             * 
             */
            ~SquareCollider() override = default;
            /**
             * @brief Construct a new Square Collider object
             * 
             * @param other 
             */
            SquareCollider(const SquareCollider& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return SquareCollider& 
             */
            SquareCollider& operator=(const SquareCollider& other) = default;

            /**
             * @brief Check if colliding with another entity
             * 
             * @return true 
             * @return false 
             */
            bool IsColliding(void) override;
            /**
             * @brief Check if colliding at a specific position
             * 
             * @param pos 
             * @return true 
             * @return false 
             */
            bool IsCollidingAtPosition(RayLib::Vector2<float> pos) override;

            /**
             * @brief Check with a circle collision
             * 
             * @param circle 
             * @return true 
             * @return false 
             */
            bool CheckCollision(RayLib::Circle& circle) override;
            /**
             * @brief Check with a rectangle collision
             * 
             * @param rec 
             * @return true 
             * @return false 
             */
            bool CheckCollision(RayLib::Rectangle& rec) override;

            /**
             * @brief Draw collision lines
             * 
             */
            void DrawLines() override;
            /**
             * @brief Get the Collision object
             * 
             * @return ECS::Entity& 
             */
            ECS::Entity& GetCollision(void) override;
            /**
             * @brief Get the Collision Position object
             * 
             * @param pos 
             * @return ECS::Entity& 
             */
            ECS::Entity& GetCollisionPosition(RayLib::Vector2<float> pos) override;

            /**
             * @brief Update current collider with entity position
             * 
             */
            void UpdateSquare(void);

            std::ostream &operator<<(std::ostream &os) override {return (os);}
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return (ptree);}

            /**
             * @brief Check if its an entity to collide with
             * 
             * @param entity 
             * @return true 
             * @return false 
             */
            bool CheckCollisionMask(ECS::Entity& entity);

            /**
             * @brief Get the Rectangle object
             * 
             * @return RayLib::Rectangle 
             */
            const RayLib::Rectangle& GetRectangle() const;
        protected:
        private:
            /**
             * @brief Raylib Rectangle
             * 
             */
            RayLib::Rectangle _rect;
    };
}

#endif /* !SQUARECOLLIDER_HPP_ */
