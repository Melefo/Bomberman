/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Camera
*/

#include "Camera.hpp"

namespace Component
{
    Camera::Camera(ECS::Entity& entity, RayLib::Camera3D& startCamera, RayLib::Vector3& target, float lerpTime)
    : camera(startCamera), _entity(entity), _transform(entity.GetComponent<Transform>()), _targetLookAt(target), _lerpTime(lerpTime)
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

        lerpPos.Lerp(_transform.position, _lerpTime);
        camera.SetPosition(lerpPos);
        camera.SetTarget(_targetLookAt);
        camera.Update();
    }

    void Camera::LerpToPos(RayLib::Vector3 position, float lerp)
    {
        _transform.position = position;
        _lerpTime = lerp;
    }

    void Camera::SetTarget(RayLib::Vector3& target)
    {
        _targetLookAt = target;
    }

    std::ostream& Camera::operator<<(std::ostream& stream)
    {
        // save camera parameters
        // target transform
        return (stream);
    }
}