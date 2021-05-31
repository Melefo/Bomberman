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

namespace Prototype
{
    class BoxCollider : public Collider {
        public:
            BoxCollider(ECS::Entity& attatchedEntity, ECS::Coordinator& coordinator, RayLib::BoundingBox bounds);
            ~BoxCollider() = default;

            bool IsColliding() override;
            bool CheckCollision(Vector3 center, float radius) override;
            bool CheckCollision(RayLib::BoundingBox& box) override;

            ECS::Entity& GetCollision() override;

        protected:
        private:
            RayLib::BoundingBox _bounds;
    };
}

#endif /* !BOXCOLLIDER_HPP_ */
