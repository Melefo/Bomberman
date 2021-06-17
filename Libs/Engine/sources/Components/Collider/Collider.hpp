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
#include <physac.h>
#include "PhysacBody.hpp"
#include "Transform.hpp"

namespace Component
{
    /**
     * @brief Collider base component class
     * 
     */
    class Collider : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Collider object
             * 
             * @param attatchedEntity
             */
            Collider(ECS::Entity& attatchedEntity, std::vector<std::string> collisionMask);
            /**
             * @brief Destroy the Collider object
             * 
             */
            ~Collider() = default;
            /**
             * @brief Construct a new Collider object
             * 
             * @param other 
             */
            Collider(const Collider& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return Collider& 
             */
            Collider& operator=(const Collider& other) = default;

            virtual RayLib::PhysacBody& GetPhysacBody() = 0;

            // ! change collision mask at runtime ??

        protected:
            /**
             * @brief List of the other entities retrieved from the coordinator
             * 
             */
            const std::list<std::unique_ptr<ECS::Entity>>& _otherEntities;
            /**
             * @brief Reference to attatched entity
             * 
             */
            ECS::Entity& _myEntity;

            std::vector<std::string> _collisionMask;
        private:

    };
}

#endif /* !COLLIDER_HPP_ */
