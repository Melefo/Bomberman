/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PlayerMovement
*/

#include "PlayerMovement.hpp"
#include <iostream>
#include "Exceptions.hpp"
#include "Transform.hpp"

namespace Component
{
    PlayerMovement::PlayerMovement(ECS::Entity& attatchedEntity, float moveSpeed, RayLib::Input input) :
    _input(input), _entity(attatchedEntity), _myPhysicsBody(_entity.GetComponent<PhysicsBody>()), _myTransform(_entity.GetComponent<Transform>()),
    _colliding(false), _speed(moveSpeed)
    {
    }

    void PlayerMovement::Update(double, ECS::Entity&)
    {
        std::vector<std::reference_wrapper<Collider>> colliders = _entity.OfType<Collider>();

        for (auto it = colliders.begin(); it != colliders.end(); it++) {
            it->get().DrawLines();
        }
       _direction = RayLib::Vector3(_input.GetHorizontalAxis(), 0.0f, _input.GetVerticalAxis());

        //std::cout << "Controller last key pressed: " << _input.GetKeyPressed() << std::endl;

    }

    void PlayerMovement::FixedUpdate(ECS::Entity& entity)
    {
        RayLib::Vector3 targetPosition = _myTransform.position + _direction * _speed;
        std::vector<std::reference_wrapper<Collider>> colliders = _entity.OfType<Collider>();

        (void) entity;
        _colliding = false;
        for (auto it = colliders.begin(); it != colliders.end(); it++) {
            if (!_colliding)
                _colliding = it->get().IsCollidingAtPosition(targetPosition);
            it->get().DrawLines();
        }

         if (!_colliding) {
            // idéalement ce serait += mais comme on a pas de drag, on ne ferait qu'accélérer
            _myPhysicsBody.velocity = _direction * _speed;
        } else {
            _myPhysicsBody.velocity = RayLib::Vector3();
        }
    }

    void PlayerMovement::LateUpdate(double, ECS::Entity&)
    {

    }
}
