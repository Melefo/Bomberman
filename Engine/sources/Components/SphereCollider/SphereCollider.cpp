/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** SphereCollider
*/

#include "SphereCollider.hpp"

namespace Component
{
    SphereCollider::SphereCollider(ECS::Entity& entity, RayLib::Vector3 center, float radius):
    Collider(entity), _center(center), _radius(radius), _transform(entity.GetComponent<Transform>())
    {
    }

    bool SphereCollider::IsColliding()
    {
        UpdatePosition();

        for (auto entityIt = _otherEntities.begin(); entityIt != _otherEntities.end(); entityIt++) {
            if (entityIt->get()->GetId() == _myEntity.GetId())
                continue;
            std::vector<std::reference_wrapper<Collider>> colliders = entityIt->get()->OfType<Collider>();

            for (auto it = colliders.begin(); it != colliders.end(); it++) {
                if (it->get().CheckCollision(_center, _radius))
                    return (true);
            }
        }
        return (false);
    }

    bool SphereCollider::IsCollidingAtPosition(RayLib::Vector3 center)
    {
        for (auto entityIt = _otherEntities.begin(); entityIt != _otherEntities.end(); entityIt++) {
            if (entityIt->get()->GetId() == _myEntity.GetId())
                continue;
            std::vector<std::reference_wrapper<Collider>> colliders = entityIt->get()->OfType<Collider>();

            for (auto it = colliders.begin(); it != colliders.end(); it++) {
                if (it->get().CheckCollision(center, _radius))
                    return (true);
            }
        }
        return (false);
    }


    bool SphereCollider::CheckCollision(RayLib::Vector3 center, float radius)
    {
        UpdatePosition();

        return (RayLib::Physics3D::CheckCollision(_center, _radius, center, radius));
    }

    bool SphereCollider::CheckCollision(RayLib::BoundingBox& box)
    {
        UpdatePosition();

        return (RayLib::Physics3D::CheckCollision(box, _center, _radius));
    }

    bool SphereCollider::CheckCollision(RayLib::Ray& ray)
    {
        UpdatePosition();

        return (RayLib::Physics3D::CheckCollision(ray, _center, _radius).HasHit());
    }


    ECS::Entity& SphereCollider::GetCollision()
    {
        UpdatePosition();

        for (auto entityIt = _otherEntities.begin(); entityIt != _otherEntities.end(); entityIt++) {
            if (entityIt->get()->GetId() == _myEntity.GetId())
                continue;
            std::vector<std::reference_wrapper<Collider>> colliders = entityIt->get()->OfType<Collider>();

            for (auto it = colliders.begin(); it != colliders.end(); it++) {
                if (it->get().CheckCollision(_center, _radius))
                    return (*(entityIt->get()));
            }
        }
        throw ECS::Exception::EntityException("Not colliding with anything");
    }

    void SphereCollider::DrawLines()
    {
        UpdatePosition();
        std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");

        window->DrawSphereWires(_center, _radius, 20, 20, GREEN);
    }

    void SphereCollider::UpdatePosition()
    {
        _center = _transform.position;
    }
}