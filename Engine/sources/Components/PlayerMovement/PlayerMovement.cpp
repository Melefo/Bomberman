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

    void PlayerMovement::FixedUpdate(ECS::Entity&)
    {
        SlipperyCollisions();

        if (!_colliding) {
            // idéalement ce serait += mais comme on a pas de drag, on ne ferait qu'accélérer
            _myPhysicsBody.velocity = _direction * _speed;
        } else {
            _myPhysicsBody.velocity = RayLib::Vector3();
        }
    }

    void PlayerMovement::SlipperyCollisions()
    {
        RayLib::Vector3 targetPosition = _myTransform.position + _direction * _speed;
        std::vector<std::reference_wrapper<Collider>> colliders = _entity.OfType<Collider>();
        RayLib::Vector3 modifiedDir = _direction;

        _colliding = false;
        for (auto it = colliders.begin(); it != colliders.end(); it++) {
            if (!_colliding)
                _colliding = it->get().IsCollidingAtPosition(targetPosition);
        }

        if (!_colliding)
            return;

        std::vector<RayLib::Vector3> newDirections;
        // check x solo
        newDirections.push_back(RayLib::Vector3(_direction.x, 0.0f, 0.0f));
        // check z solo
        newDirections.push_back(RayLib::Vector3(0.0f, 0.0f, _direction.z));

        if (abs(_direction.z) < 0.1f && abs(_direction.x) > 0.1f) {
            newDirections.push_back(RayLib::Vector3(_direction.x, 0.0f, -_direction.x));
            newDirections.push_back(RayLib::Vector3(_direction.x, 0.0f, _direction.x));
        }
        if (abs(_direction.x) < 0.1f && abs(_direction.z) > 0.1) {
            newDirections.push_back(RayLib::Vector3(_direction.z, 0.0f, _direction.z));
            newDirections.push_back(RayLib::Vector3(-_direction.z, 0.0f, _direction.z));
        }

        for (auto it = newDirections.begin(); it != newDirections.end(); it++) {
            if (it->x == 0.0f && it->z == 0.0f)
                continue;
            if (!CheckCollidersPos(colliders, _myTransform.position + *it * _speed)) {
                _colliding = false;
                _direction = *it;
                return;
            }
        }
    }

    bool PlayerMovement::CheckCollidersPos(std::vector<std::reference_wrapper<Collider>> colliders, RayLib::Vector3 position)
    {
        for (auto it = colliders.begin(); it != colliders.end(); it++) {
            if (it->get().IsCollidingAtPosition(position))
                return (true);
        }
        return (false);
    }


    void PlayerMovement::LateUpdate(double, ECS::Entity&)
    {

    }

    std::ostream& PlayerMovement::operator<<(std::ostream& stream)
    {
        // save movement keys
        // speed
        return (stream);
    }
}
