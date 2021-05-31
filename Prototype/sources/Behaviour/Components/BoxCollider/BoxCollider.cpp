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

namespace Prototype
{
    BoxCollider::BoxCollider(ECS::Entity& attatchedEntity, ECS::Coordinator& coordinator, RayLib::BoundingBox bounds)
    : Collider(attatchedEntity, coordinator), _bounds(bounds)
    {
    }

    bool BoxCollider::IsColliding()
    {
        UpdateBounds();

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

    ECS::Entity& BoxCollider::GetCollision()
    {
        UpdateBounds();

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

        window->DrawCubeWires(_bounds.GetCenter(), scale, GREEN);
    }

    void BoxCollider::UpdateBounds()
    {
        Transform& transform = _myEntity.GetComponent<Transform>();

        _bounds.InitFromCube(transform.position, transform.scale);
    }
}

