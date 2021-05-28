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

namespace Prototype
{
    class PlayerMovement : public IBehaviour {
        public:
            PlayerMovement(ECS::Entity& attatchedEntity, float moveSpeed);
            ~PlayerMovement() override = default;

            void Update(float dt) override;

        protected:
        private:
            RayLib::Input _input;
            ECS::Entity& _entity;
            PhysicsBody& _myPhysicsBody;
            float _speed;
    };
}

#endif /* !PLAYERMOVEMENT_HPP_ */
