/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PlayerMovement
*/

#include "PlayerMovement.hpp"
#include <iostream>
#include "Exceptions.hpp"

namespace Prototype
{
    PlayerMovement::PlayerMovement(ECS::Entity& attatchedEntity, float moveSpeed) :
    _input(), _entity(attatchedEntity), _myPhysicsBody(_entity.GetComponent<PhysicsBody>()), _myTransform(_entity.GetComponent<Transform>())
    {
        _speed = moveSpeed;
        _colliding = false;
    }

    void PlayerMovement::Update(float dt)
    {
        if (!_colliding) {
            // idéalement ce serait += mais comme on a pas de drag, on ne ferait qu'accélérer
            _myPhysicsBody.velocity = RayLib::Vector3(_input.GetHorizontalAxis(),
                                                    0.0f,
                                                    _input.GetVerticalAxis()) * _speed;
        } else {
            _myPhysicsBody.velocity = RayLib::Vector3();
        }
    }

    void PlayerMovement::FixedUpdate(ECS::Entity& entity)
    {
        PhysicsBody& physicsBody = _entity.GetComponent<PhysicsBody>();
        RayLib::Vector3 targetPosition = _myTransform.position + physicsBody.velocity;
        std::vector<std::reference_wrapper<Collider>> colliders = _entity.OfType<Collider>();

        _colliding = false;
        for (auto it = colliders.begin(); it != colliders.end(); it++) {
            if (!_colliding)
                _colliding = it->get().IsCollidingAtPosition(targetPosition);
            it->get().DrawLines();
        }
    }
}
