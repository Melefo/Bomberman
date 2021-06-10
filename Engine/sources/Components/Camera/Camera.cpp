/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Camera
*/

#include "Camera.hpp"
#include <iostream>

namespace Component
{
    Camera::Camera(ECS::Entity& entity, RayLib::Camera3D& startCamera, RayLib::Vector3& target, float lerpTime)
    : camera(startCamera), _entity(entity), _transform(entity.GetComponent<Transform>()), _targetLookAt(target), _lerpTime(lerpTime)
    {
            std::cout << "Pos X " << _transform.position.x << std::endl;
            std::cout << "Pos Y " << _transform.position.y << std::endl;
            std::cout << "Pos Z " << _transform.position.z << std::endl;
    }

    void Camera::Update(double, ECS::Entity&)
    {
        /*const RayLib::Vector3 pos = camera.GetPosition();
        RayLib::Vector3 lerpPos = _transform.position;

        //lerpPos.Lerp(_transform.position, _lerpTime);
        //camera.SetPosition(lerpPos);

        camera.SetPosition(_targetLookAt + _transform.position);

        camera.SetTarget(_targetLookAt);
        camera.Update();*/
    }

    void Camera::FixedUpdate(ECS::Entity&)
    {

    }

    void Camera::LateUpdate(double, ECS::Entity&)
    {
        const RayLib::Vector3 pos = camera.GetPosition();
        RayLib::Vector3 lerpPos = _transform.position;


        camera.SetPosition(_targetLookAt + _transform.position);

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
}