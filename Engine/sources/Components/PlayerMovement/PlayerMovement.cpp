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
    PlayerMovement::PlayerMovement(ECS::Entity& attatchedEntity, float moveSpeed) :
    _input(), _entity(attatchedEntity), _myPhysicsBody(_entity.GetComponent<PhysicsBody>())
    {
        _speed = moveSpeed;
    }

    void PlayerMovement::Update(float dt)
    {
        int colliding = 0;
        Transform& transform = _entity.GetComponent<Transform>();

        RayLib::Vector3 targetPosition = transform.position + (RayLib::Vector3(_input.GetHorizontalAxis(),
                                                                              0.0f,
                                                                              _input.GetVerticalAxis()) * _speed * dt);

        std::vector<std::reference_wrapper<Collider>> colliders = _entity.OfType<Collider>();

        for (auto it = colliders.begin(); it != colliders.end(); it++) {
            colliding += it->get().IsCollidingAtPosition(targetPosition) ? 1 : 0;
            it->get().DrawLines();
        }

        if (colliding == 0) {
            // idéalement ce serait += mais comme on a pas de drag, on ne ferait qu'accélérer
            _myPhysicsBody.velocity = RayLib::Vector3(_input.GetHorizontalAxis(),
                                                    0.0f,
                                                    _input.GetVerticalAxis()) * _speed;
        } else {
            _myPhysicsBody.velocity = RayLib::Vector3();
        }
    }
}
