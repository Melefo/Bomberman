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

namespace Component
{
    /**
     * @brief Collision system
     * 
     */
    class CollisionSystem {
        public:
            /**
             * @brief Construct a new Collision System object
             * 
             */
            CollisionSystem() = default;
            /**
             * @brief Destroy the Collision System object
             * 
             */
            ~CollisionSystem() = default;
            /**
             * @brief Construct a new Collision System object
             * 
             * @param other 
             */
            CollisionSystem(const CollisionSystem& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return CollisionSystem& 
             */
            CollisionSystem& operator=(const CollisionSystem& other) = default;

            /**
             * @brief Returns all entities in the given sphere
             * 
             * @param coordinator 
             * @param center 
             * @param radius 
             * @return std::vector<std::reference_wrapper<ECS::Entity>> 
             */
            static std::vector<std::reference_wrapper<ECS::Entity>> OverlapSphere(ECS::Coordinator& coordinator, RayLib::Vector3 center, float radius);
            /**
             * @brief Returns all entities in the given box
             * 
             * @param coordinator 
             * @param box 
             * @return std::vector<std::reference_wrapper<ECS::Entity>> 
             */
            static std::vector<std::reference_wrapper<ECS::Entity>> OverlapBox(ECS::Coordinator& coordinator, RayLib::BoundingBox box);
            //static std::vector<std::reference_wrapper<ECS::Entity>> RayCast(ECS::Coordinator& coordinator, RayLib::Vector3 center, float distance, RayLib::Vector3 direction);

        protected:
        private:

    };
}

#endif /* !COLLISIONSYSTEM_HPP_ */
