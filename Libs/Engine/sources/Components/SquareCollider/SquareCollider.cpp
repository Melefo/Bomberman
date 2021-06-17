/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** SquareCollider
*/

#include "SquareCollider.hpp"
#include "EngineExceptions.hpp"

namespace Component
{
    SquareCollider::SquareCollider(ECS::Entity& attatchedEntity, std::vector<std::string> collisionMask, RayLib::Vector2<float> pos, RayLib::Vector2<float> scale) :
    Collider(attatchedEntity, collisionMask), _rect(pos.x, pos.y, scale.x, scale.y)
    {
        if (attatchedEntity.HasComponent<Transform>())
            UpdateSquare();
    }

    bool SquareCollider::IsColliding(void)
    {
        UpdateSquare();

        for (auto entityIt = _otherEntities.begin(); entityIt != _otherEntities.end(); entityIt++) {
            if (entityIt->get()->GetId() == _myEntity.GetId())
                continue;
            if (std::find(_collisionMask.begin(), _collisionMask.end(), entityIt->get()->GetTag()) == _collisionMask.end())
                continue;
            std::vector<std::reference_wrapper<Collider>> colliders = entityIt->get()->OfType<Collider>();

            for (auto it = colliders.begin(); it != colliders.end(); it++) {
                if (it->get().CheckCollision(_rect))
                    return (true);
            }
        }
        return (false);
    }

    bool SquareCollider::IsCollidingAtPosition(RayLib::Vector2<float> pos)
    {
        Transform& transform = _myEntity.GetComponent<Transform>();

        RayLib::Rectangle tmpRect(pos.x, pos.y, transform.scale.x, transform.scale.z);

        for (auto entityIt = _otherEntities.begin(); entityIt != _otherEntities.end(); entityIt++) {
            if (entityIt->get()->GetId() == _myEntity.GetId())
                continue;
            if (std::find(_collisionMask.begin(), _collisionMask.end(), entityIt->get()->GetTag()) == _collisionMask.end())
                continue;
            std::vector<std::reference_wrapper<Collider>> colliders = entityIt->get()->OfType<Collider>();

            for (auto it = colliders.begin(); it != colliders.end(); it++) {
                if (it->get().CheckCollision(tmpRect))
                    return (true);
            }
        }
        return (false);
    }

    void SquareCollider::DrawLines()
    {
        _rect.DrawRectangleLines(GREEN);
    }

    ECS::Entity& SquareCollider::GetCollision(void)
    {
        UpdateSquare();

        for (auto entityIt = _otherEntities.begin(); entityIt != _otherEntities.end(); entityIt++) {
            if (entityIt->get()->GetId() == _myEntity.GetId())
                continue;
            if (std::find(_collisionMask.begin(), _collisionMask.end(), entityIt->get()->GetTag()) == _collisionMask.end())
                continue;
            std::vector<std::reference_wrapper<Collider>> colliders = entityIt->get()->OfType<Collider>();

            for (auto it = colliders.begin(); it != colliders.end(); it++) {
                if (it->get().CheckCollision(_rect))
                    return (*(entityIt->get()));
            }
        }
        throw Engine::Exception::EngineException("Not colliding with anything");
    }

    ECS::Entity& SquareCollider::GetCollisionPosition(RayLib::Vector2<float> pos)
    {
        Transform& transform = _myEntity.GetComponent<Transform>();

        RayLib::Rectangle tmpRect(pos.x - transform.scale.x / 2.0f, pos.y - transform.scale.y / 2.0f, transform.scale.x, transform.scale.z);

        for (auto entityIt = _otherEntities.begin(); entityIt != _otherEntities.end(); entityIt++) {
            if (entityIt->get()->GetId() == _myEntity.GetId())
                continue;
            if (std::find(_collisionMask.begin(), _collisionMask.end(), entityIt->get()->GetTag()) == _collisionMask.end())
                continue;
            std::vector<std::reference_wrapper<Collider>> colliders = entityIt->get()->OfType<Collider>();

            for (auto it = colliders.begin(); it != colliders.end(); it++) {
                if (it->get().CheckCollision(tmpRect))
                    return (*(entityIt->get()));
            }
        }
        throw Engine::Exception::EngineException("Not colliding with anything");
    }

    bool SquareCollider::CheckCollision(RayLib::Circle& circle)
    {
        UpdateSquare();
        return (RayLib::Physics2D::CheckCollision(_rect, circle));
    }

    bool SquareCollider::CheckCollision(RayLib::Rectangle& rec)
    {
        UpdateSquare();
        return (RayLib::Physics2D::CheckCollision(_rect, rec));
    }

    const RayLib::Rectangle& SquareCollider::GetRectangle() const
    {
        return this->_rect;
    }

    void SquareCollider::UpdateSquare(void)
    {
        if (!_myEntity.HasComponent<Transform>())
            return;
        Transform& transform = _myEntity.GetComponent<Transform>();

        _rect.width = transform.scale.x;
        _rect.height = transform.scale.z;
        _rect.x = transform.position.x - transform.scale.x / 2.0f;
        _rect.y = transform.position.z - transform.scale.z / 2.0f;
    }
}