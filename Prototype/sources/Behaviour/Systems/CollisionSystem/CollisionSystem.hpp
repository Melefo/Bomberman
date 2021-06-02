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
    class CollisionSystem : public ECS::ASystem {
        public:
            CollisionSystem(ECS::Coordinator& coordinator);
            ~CollisionSystem() override = default;

            //std::vector<std::reference_wrapper<ECS::Entity>> OverlapSphere(RayLib::Vector3 center, float radius);

            //dynamic_cast<T&>

        protected:
        private:
            ECS::Coordinator& _coordinator;
    };
}

#endif /* !COLLISIONSYSTEM_HPP_ */
