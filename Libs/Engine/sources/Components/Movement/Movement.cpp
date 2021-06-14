/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Movement
*/

#include "Movement.hpp"
#include <iostream>
#include "Exceptions.hpp"

namespace Component
{
    Movement::Movement(ECS::Entity& attatchedEntity, float moveSpeed) :
    _entity(attatchedEntity), _colliding(false), _speed(moveSpeed), _startSpeed(moveSpeed), _bonusTime(0.0f)
    {
        _collisionMask.push_back("Wall");
        _collisionMask.push_back("Box");
    }

    void Movement::Update(double, ECS::Entity&)
    {
        float frameTime = RayLib::Window::GetInstance(0, "")->GetFrameTime();

        if (_bonusTime > 0.0f) {
            _bonusTime -= frameTime;
            if (_bonusTime <= 0.0f) {
                _bonusTime = 0.0f;
                _speed = _startSpeed;
            }
        }

    }

    // todo move this to update to fix stuttering, but then fix the speed
    void Movement::FixedUpdate(ECS::Entity&)
    {
        SlipperyCollisions();

        if  (_entity.HasComponent<PhysicsBody>()) {
            PhysicsBody& physicsBody = _entity.GetComponent<PhysicsBody>();

            if (!_colliding) {
                // ! cache ?
                physicsBody.velocity = direction * _speed;
            } else {
                physicsBody.velocity = RayLib::Vector3();
            }
        }
    }

    void Movement::SlipperyCollisions()
    {
        RayLib::Vector3 targetPosition = RayLib::Vector3();
        RayLib::Vector3 currentPos = RayLib::Vector3();
        if (_entity.HasComponent<Transform>()) {
            Transform& transform = _entity.GetComponent<Transform>();
            targetPosition = transform.position + direction * _speed;
            currentPos = transform.position;
        } else {
            return;
        }

        std::vector<std::reference_wrapper<Collider>> colliders = _entity.OfType<Collider>();
        RayLib::Vector3 modifiedDir = direction;

        _colliding = CheckCollidersPos(colliders, targetPosition, _collisionMask);

        if (!_colliding)
            return;

        std::vector<RayLib::Vector3> newDirections;
        // check x solo
        newDirections.push_back(RayLib::Vector3(direction.x, 0.0f, 0.0f));
        // check z solo
        newDirections.push_back(RayLib::Vector3(0.0f, 0.0f, direction.z));

        float iterations = 10.0;
        for (float i = 0; i < iterations; i++) {
            if (abs(direction.z) < 0.1f && abs(direction.x) > 0.1f) {
                newDirections.push_back(RayLib::Vector3(direction.x, 0.0f, -direction.x * i));
                newDirections.push_back(RayLib::Vector3(direction.x, 0.0f, direction.x * i));
            }
            if (abs(direction.x) < 0.1f && abs(direction.z) > 0.1) {
                newDirections.push_back(RayLib::Vector3(direction.z * i, 0.0f, direction.z));
                newDirections.push_back(RayLib::Vector3(-direction.z * i, 0.0f, direction.z));
            }
        }

        for (auto it = newDirections.begin(); it != newDirections.end(); it++) {
            if (it->x == 0.0f && it->z == 0.0f)
                continue;
            if (!CheckCollidersPos(colliders, currentPos + *it * _speed, _collisionMask)) {
                _colliding = false;
                direction = *it;
                return;
            }
        }
    }

    void Movement::BoostSpeed(float bonusSpeed, float time)
    {
        _bonusTime = time;
        _speed += bonusSpeed;
    }

    bool Movement::CheckCollidersPos(std::vector<std::reference_wrapper<Collider>> colliders, RayLib::Vector3 position, std::vector<std::string> collisionMask)
    {
        for (auto it = colliders.begin(); it != colliders.end(); it++) {
            if (it->get().IsCollidingAtPosition(position, collisionMask)) {
                ECS::Entity& other = it->get().GetCollisionPosition(position, collisionMask);
                if (std::find(collisionMask.begin(), collisionMask.end(), other.GetTag()) != collisionMask.end())
                    return (true);
            }
        }
        return (false);
    }


    void Movement::LateUpdate(double, ECS::Entity&)
    {

    }

}
