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
    Movement::Movement(ECS::Entity& attatchedEntity, float moveSpeed, float maxSpeed) :
    _entity(attatchedEntity), _colliding(false), _speed(moveSpeed), _startSpeed(moveSpeed), _bonusTime(0.0f), _maxSpeed(maxSpeed)
    {
        _collisionMask.push_back("Wall");
        _collisionMask.push_back("Box");
    }

    void Movement::Update(double, ECS::Entity& entity)
    {
        float frameTime = RayLib::Window::GetInstance(0, "")->GetFrameTime();

        if (_bonusTime > 0.0f) {
            _bonusTime -= frameTime;
            if (_bonusTime <= 0.0f) {
                _bonusTime = 0.0f;
                _speed = _startSpeed;
            }
        }

        // !rotate based on direction
        Transform& transform = _entity.GetComponent<Transform>();
        RayLib::Vector3 targetRot = RayLib::Vector3(transform.rotation.x, transform.rotation.y, 0.0f);

        if (abs(direction.x) > 0.0f)
            targetRot.y = direction.x * -90.0f;
        if (direction.z > 0.0f)
            targetRot.y = 0.0f;
        else if (direction.z < 0.0f)
            targetRot.y = 180.0f;


        transform.rotation.Lerp(targetRot, 0.5f);


        if (entity.HasComponent<Component::Animator>()) {
            Animator& animator = entity.GetComponent<Component::Animator>();
            const std::string& animState = animator.GetState();

            if (direction != RayLib::Vector3() && animState == "Idle") {
                animator.SetState("Run");
            } else if (direction == RayLib::Vector3() && animState == "Run") {
                animator.SetState("Idle");
            }
        }
    }

    void Movement::FixedUpdate(ECS::Entity&)
    {
        SlipperyCollisions();

        if  (_entity.HasComponent<PhysicsBody>()) {
            PhysicsBody& physicsBody = _entity.GetComponent<PhysicsBody>();

            if (_speed > _maxSpeed)
                _speed = _maxSpeed;

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
