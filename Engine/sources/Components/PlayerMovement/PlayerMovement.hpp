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
    class PlayerMovement : public IBehaviour {
        public:
            PlayerMovement(ECS::Entity& attatchedEntity, float moveSpeed);
            ~PlayerMovement() override = default;

            void Update(double dt) override;
            void FixedUpdate(ECS::Entity& entity) override;

        protected:
        private:
            RayLib::Input _input;
            ECS::Entity& _entity;
            PhysicsBody& _myPhysicsBody;
            Transform& _myTransform;
            bool _colliding;
            float _speed;
            RayLib::Vector3 _direction;

    };
}

#endif /* !PLAYERMOVEMENT_HPP_ */
