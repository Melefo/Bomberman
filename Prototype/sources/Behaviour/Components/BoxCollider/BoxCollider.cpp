/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** BoxCollider
*/

#include "BoxCollider.hpp"
#include "Exceptions.hpp"

namespace Prototype
{
    BoxCollider::BoxCollider(ECS::Entity& attatchedEntity, ECS::Coordinator& coordinator, RayLib::BoundingBox bounds)
    : Collider(attatchedEntity, coordinator), _bounds(bounds)
    {
    }

    bool BoxCollider::IsColliding()
    {
        for (auto it = _otherEntities.begin(); it != _otherEntities.end(); it++) {
            if (it->get()->GetId() == _myEntity.GetId())
                continue;
            try {
                Collider& otherCollider = it->get()->GetComponent<Collider>();
                if (otherCollider.CheckCollision(_bounds))
                    return (true);
            } catch(const ECS::Exception::EntityException& e) {

            }
        }
        return (false);
    }

    bool BoxCollider::CheckCollision(Vector3 center, float radius)
    {
        return (RayLib::Physics3D::CheckCollision(_bounds, center, radius));
    }

    bool BoxCollider::CheckCollision(RayLib::BoundingBox& box)
    {
        return (RayLib::Physics3D::CheckCollision(_bounds, box));
    }

    ECS::Entity& BoxCollider::GetCollision()
    {
        for (auto it = _otherEntities.begin(); it != _otherEntities.end(); it++) {
            if (it->get()->GetId() == _myEntity.GetId())
                continue;
            try {
                Collider& otherCollider = it->get()->GetComponent<Collider>();
                if (otherCollider.CheckCollision(_bounds))
                    return (*(it->get()));
            } catch(const ECS::Exception::EntityException& e) {

            }
        }
        throw ECS::Exception::EntityException("Not colliding with anything");
    }

}

