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

class SquareCollider : public Component::Collider {
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
         * @brief Get the Rectangle object
         * 
         * @return RayLib::Rectangle 
         */
        RayLib::Rectangle GetRectangle() const;
    protected:
    private:
        /**
         * @brief Raylib Rectangle
         * 
         */
        RayLib::Rectangle _rect;
        //var rectangle
};

#endif /* !SQUARECOLLIDER_HPP_ */
