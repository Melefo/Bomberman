/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Collider
*/

#include "Collider.hpp"
#include <iostream>

namespace Component
{
    Collider::Collider(ECS::Entity& attatchedEntity, std::vector<std::string> collisionMask)
     : _otherEntities(ECS::Coordinator::GetInstance("", 0.02f)->GetEntities()), _myEntity(attatchedEntity), _collisionMask(collisionMask),
     _myBody(RayLib::Vector2<float>(), 0, 0, 10.0f);
    {
        /*if (_myEntity.HasComponent<Transform>()) {
            Transform& transform = _myEntity.GetComponent<Transform>();
            _myBody.SetPosition(RayLib::Vector2<float>(transform.position.x, transform.position.z));
            _myBody.SetScale(RayLib::Vector2<float>(transform.scale.x, transform.scale.z));
        }*/
    }

    bool Collider::IsColliding()
    {
        return (false);
    }
}
