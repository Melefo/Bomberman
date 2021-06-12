/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Draggable
*/

#include "Draggable.hpp"

namespace Component
{
    Draggable::Draggable(ECS::Entity& attatchedEntity, RayLib::Camera3D& camera) :
    _entity(attatchedEntity), _camera(camera), _transform(_entity.GetComponent<Transform>())
    {
        _colliders = _entity.OfType<Collider>();
        _selected = false;
    }

    void Draggable::Update(double, ECS::Entity&)
    {
        RayLib::Ray ray;

        // ! move to window so we don't depend on camera ?
        ray = _camera.GetMouseRay(RayLib::Mouse::GetPosition());

        if (RayLib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (!_selected)
            {
                // Check collision between ray and box
                for (auto it = _colliders.begin(); it != _colliders.end(); it++) {
                    _selected = it->get().CheckCollision(ray);
                    if (_selected)
                        break;
                }
            }
        }
        if (RayLib::Mouse::IsButtonPressed(MOUSE_BUTTON_RIGHT))
            _selected = false;

        // if selected, move with mouse flat on plane (y = 0)
        if (_selected) {
            RayLib::RayCollision hitInfo = RayLib::Physics3D::CheckCollision(ray, 0.0f);

            if (hitInfo.HasHit()) {
                // snap position
                RayLib::Vector3 position = hitInfo.GetPosition();
                _transform.position = RayLib::Vector3(round(position.x), position.y, round(position.z));
            }
        }
    }

    void Draggable::FixedUpdate(ECS::Entity&)
    {

    }

    void Draggable::LateUpdate(double, ECS::Entity&)
    {
        
    }
}

