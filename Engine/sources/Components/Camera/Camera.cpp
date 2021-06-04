/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Camera
*/

#include "Camera.hpp"

namespace Component
{
    Camera::Camera(ECS::Entity& entity, RayLib::Camera3D& startCamera, Transform& target)
    : camera(startCamera), _entity(entity), _transform(entity.GetComponent<Transform>()), _targetLookat(target)
    {
    }

    void Camera::Update(double, ECS::Entity&)
    {

    }

    void Camera::FixedUpdate(ECS::Entity&)
    {

    }

    void Camera::LateUpdate(double, ECS::Entity&)
    {
        const RayLib::Vector3 pos = camera.GetPosition();
        RayLib::Vector3 lerpPos = pos;

        lerpPos.Lerp(_transform.position, 0.25f);
        camera.SetPosition(lerpPos);
        camera.SetTarget(_targetLookat.position);
        camera.Update();
    }
}