/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PlayerMovement
*/

#ifndef PLAYERMOVEMENT_HPP_
#define PLAYERMOVEMENT_HPP_

#include "IBehaviour.hpp"
#include "Input.hpp"
#include "PhysicsBody.hpp"
#include "Entity.hpp"
#include "Collider.hpp"
#include "Transform.hpp"

namespace Component
{
    /**
     * @brief Behaviour script responsible for moving an entity
     * 
     */
    class PlayerMovement : public IBehaviour {
        public:
            /**
             * @brief Construct a new Player Movement object
             * 
             * @param attatchedEntity 
             * @param moveSpeed 
             */
            PlayerMovement(ECS::Entity& attatchedEntity, float moveSpeed, RayLib::Input input=RayLib::Input());
            /**
             * @brief Destroy the Player Movement object
             * 
             */
            ~PlayerMovement() override = default;
            /**
             * @brief Construct a new Player Movement object
             * 
             * @param other 
             */
            PlayerMovement(const PlayerMovement& other) = default;
            /**
             * @brief Assignement operator
             * 
             * @param other 
             * @return PlayerMovement& 
             */
            PlayerMovement& operator=(const PlayerMovement& other) = default;

            /**
             * @brief Used to sample the input
             * 
             * @param dt 
             */
            void Update(double dt, ECS::Entity& entity) override;
            /**
             * @brief Used to modify the velocity regularly
             * 
             * @param entity 
             */
            void FixedUpdate(ECS::Entity& entity) override;

            /**
             * @brief 
             * 
             * @param dt 
             * @param entity 
             */
            void LateUpdate(double dt, ECS::Entity& entity) override;

        protected:
        private:
            /**
             * @brief Input instance to get movement keys
             * 
             */
            RayLib::Input _input;
            /**
             * @brief Ref to entity for transform/physics
             * 
             */
            ECS::Entity& _entity;
            /**
             * @brief Reference to physicsbody
             * 
             */
            PhysicsBody& _myPhysicsBody;
            /**
             * @brief Reference to transform
             * 
             */
            Transform& _myTransform;
            /**
             * @brief Is the entity colliding or not (i.e. can it move)
             * 
             */
            bool _colliding;
            /**
             * @brief Speed multiplier
             * 
             */
            float _speed;
            /**
             * @brief Direction used to direct velocity
             * 
             */
            RayLib::Vector3 _direction;

    };
}

#endif /* !PLAYERMOVEMENT_HPP_ */
