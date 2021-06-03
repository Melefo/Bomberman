/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include "ASystem.hpp"
#include "Entity.hpp"
#include "Collider.hpp"
#include "Coordinator.hpp"
#include <vector>

namespace Prototype
{
    class CollisionSystem {
        public:
            CollisionSystem() = default;
            ~CollisionSystem() = default;

            static std::vector<std::reference_wrapper<ECS::Entity>> OverlapSphere(ECS::Coordinator& coordinator, RayLib::Vector3 center, float radius);

        protected:
        private:

    };
}

#endif /* !COLLISIONSYSTEM_HPP_ */
