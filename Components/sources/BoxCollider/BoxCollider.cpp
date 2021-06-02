/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** BoxCollider
*/

#include "BoxCollider.hpp"
#include "Exceptions.hpp"
#include "Window.hpp"
#include "Transform.hpp"
#include <iostream>

namespace Component
{
    BoxCollider::BoxCollider(ECS::Entity& attatchedEntity, ECS::Coordinator& coordinator, RayLib::Vector3 scale)
    : Collider(attatchedEntity, coordinator), _bounds(RayLib::Vector3(), scale)
    {
        Transform& transform = attatchedEntity.GetComponent<Transform>();
        _bounds.InitFromCube(transform.position, scale);
        _scale = scale;
    }

    bool BoxCollider::IsColliding()
    {
        UpdateBounds();

        for (auto entityIt = _otherEntities.begin(); entityIt != _otherEntities.end(); entityIt++) {
            if (entityIt->get()->GetId() == _myEntity.GetId())
                continue;
            std::vector<std::reference_wrapper<Collider>> colliders = entityIt->get()->OfType<Collider>();

            for (auto it = colliders.begin(); it != colliders.end(); it++) {
                if (it->get().CheckCollision(_bounds))
                    return (true);
            }
        }
        return (false);
    }

    bool BoxCollider::IsCollidingAtPosition(RayLib::Vector3 center)
    {
        RayLib::Vector3 scale = RayLib::Vector3(_bounds.GetBounds().max) - RayLib::Vector3(_bounds.GetBounds().min);
        RayLib::BoundingBox tmpBox = RayLib::BoundingBox(RayLib::Vector3(), RayLib::Vector3());

        tmpBox.InitFromCube(center, scale);

        for (auto entityIt = _otherEntities.begin(); entityIt != _otherEntities.end(); entityIt++) {
            if (entityIt->get()->GetId() == _myEntity.GetId())
                continue;
            std::vector<std::reference_wrapper<Collider>> colliders = entityIt->get()->OfType<Collider>();

            for (auto it = colliders.begin(); it != colliders.end(); it++) {
                if (it->get().CheckCollision(tmpBox))
                    return (true);
            }
        }
        return (false);
    }


    bool BoxCollider::CheckCollision(RayLib::Vector3 center, float radius)
    {
        UpdateBounds();

        return (RayLib::Physics3D::CheckCollision(_bounds, center, radius));
    }

    bool BoxCollider::CheckCollision(RayLib::BoundingBox& box)
    {
        UpdateBounds();

        return (RayLib::Physics3D::CheckCollision(_bounds, box));
    }

    bool BoxCollider::CheckCollision(RayLib::Ray& ray)
    {
        UpdateBounds();

        return (RayLib::Physics3D::CheckCollision(ray, _bounds).HasHit());
    }


    ECS::Entity& BoxCollider::GetCollision()
    {
        UpdateBounds();

        for (auto entityIt = _otherEntities.begin(); entityIt != _otherEntities.end(); entityIt++) {
            if (entityIt->get()->GetId() == _myEntity.GetId())
                continue;
            std::vector<std::reference_wrapper<Collider>> colliders = entityIt->get()->OfType<Collider>();

            for (auto it = colliders.begin(); it != colliders.end(); it++) {
                if (it->get().CheckCollision(_bounds))
                    return (*(entityIt->get()));
            }
        }
        throw ECS::Exception::EntityException("Not colliding with anything");
    }

    void BoxCollider::DrawLines()
    {
        UpdateBounds();
        std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");

        RayLib::Vector3 scale = RayLib::Vector3(_bounds.GetBounds().max) - RayLib::Vector3(_bounds.GetBounds().min);
        /*_minVertex = Vector3(cubePos.x - cubeScale.x / 2.0f,
                             cubePos.y - cubeScale.y / 2.0f,
                             cubePos.z - cubeScale.z / 2.0f);
        _maxVertex = Vector3(cubePos.x + cubeScale.x / 2.0f,
                             cubePos.y + cubeScale.y / 2.0f,
                             cubePos.z + cubeScale.z / 2.0f);*/

        window->DrawBoundingBox(_bounds, GREEN);
    }

    void BoxCollider::UpdateBounds()
    {
        Transform& transform = _myEntity.GetComponent<Transform>();

        // use transform scale proportionnally ?
        _bounds.InitFromCube(transform.position, _scale);
    }
}

