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

            bool IsColliding(void) override;
            bool IsCollidingAtPosition(RayLib::Vector2<float> pos) override;

            bool CheckCollision(RayLib::Circle& circle) override;
            bool CheckCollision(RayLib::Rectangle& rec) override;

            void DrawLines() override;
            ECS::Entity& GetCollision(void) override;
            ECS::Entity& GetCollisionPosition(RayLib::Vector2<float> pos) override;

            void UpdateSquare(void);

            std::ostream &operator<<(std::ostream &os) override {return (os);}
            std::istream &operator>>(std::istream &is) override {return (is);}
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return (ptree);}


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
