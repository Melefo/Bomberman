/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** BoxCollider
*/

#include "BoxCollider.hpp"

namespace Component
{
    BoxCollider::BoxCollider(ECS::Entity& attatchedEntity,
    RayLib::Vector2<float> position,
    std::vector<std::string> colMask,
    RayLib::Vector2<float> scale) : Collider(attatchedEntity, colMask), _myBody(0.0f, 1.0f, 1.0f, 10.0f)
    {
        if (_myEntity.HasComponent<Transform>()) {
            UpdateBody();
        }
    }

    void BoxCollider::UpdateBody()
    {
        Transform& transform = _myEntity.GetComponent<Transform>();
        _myBody.SetPosition(RayLib::Vector2<float>(transform.position.x, transform.position.z));
        _myBody.SetRectScale(RayLib::Vector2<float>(transform.scale.x, transform.scale.z));
    }

    RayLib::PhysacBody& BoxCollider::GetPhysacBody()
    {
        return (_myBody);
    }
}
