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

namespace Prototype
{
    class Collider : public ECS::IComponent {
        public:
            Collider(ECS::Entity& attatchedEntity, ECS::Coordinator& coordinator);
            ~Collider() = default;

            virtual bool IsColliding();
            virtual bool CheckCollision(Vector3 center, float radius) = 0;
            virtual bool CheckCollision(RayLib::BoundingBox& box) = 0;

            virtual ECS::Entity& GetCollision() = 0;

        protected:
            const std::vector<std::unique_ptr<ECS::Entity>>& _otherEntities;
            ECS::Entity& _myEntity;
        private:

    };
}

#endif /* !COLLIDER_HPP_ */
