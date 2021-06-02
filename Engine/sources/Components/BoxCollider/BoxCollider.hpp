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
    class BoxCollider : public Collider {
        public:
            BoxCollider(ECS::Entity& attatchedEntity, ECS::Coordinator& coordinator,
                        RayLib::Vector3 scale=RayLib::Vector3(1.0f, 1.0f, 1.0f));
            ~BoxCollider() = default;

            bool IsColliding() override;
            bool CheckCollision(RayLib::Vector3 center, float radius) override;
            bool CheckCollision(RayLib::BoundingBox& box) override;
            bool CheckCollision(RayLib::Ray& ray) override;

            bool IsCollidingAtPosition(RayLib::Vector3 center) override;

            void DrawLines() override;
            void UpdateBounds();

            ECS::Entity& GetCollision() override;

        protected:
        private:
            RayLib::Vector3 _scale;
            RayLib::BoundingBox _bounds;
    };
}

#endif /* !BOXCOLLIDER_HPP_ */
