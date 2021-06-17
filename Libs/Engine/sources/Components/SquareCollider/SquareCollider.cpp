/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** SquareCollider
*/

#include "SquareCollider.hpp"

namespace Component
{
    Collider::SquareCollider(ECS::Entity& attatchedEntity, std::vector<std::string> collisionMask, RayLib::Vector2<float> pos, RayLib::Vector2<float> scale) :
    _rect(pos.x, pos.y, scale.x, scale.y)
    {}

    RayLib::Rectangle SquareCollider::GetRectangle() const
    {
        return this->_rect;
    }
}