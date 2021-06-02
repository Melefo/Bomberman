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

            static void SetSystem(CollisionSystem& colSystem);
            static std::vector<std::reference_wrapper<ECS::Entity>> OverlapSphere(RayLib::Vector3 center, float radius);

            //dynamic_cast<T&>

            ECS::Coordinator& GetCoordinator();

        protected:
        private:
            ECS::Coordinator& _coordinator;
            static std::unique_ptr<std::reference_wrapper<CollisionSystem>> _colSystem;

    };
}

#endif /* !COLLISIONSYSTEM_HPP_ */
