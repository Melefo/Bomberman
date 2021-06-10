/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Camera
*/

#include "Camera.hpp"
#include <iostream>
#include "Window.hpp"

namespace Component
{
    Camera::Camera(ECS::Entity& entity, RayLib::Camera3D& startCamera, float lerpTime)
    : camera(startCamera), _entity(entity), _transform(entity.GetComponent<Transform>()), _lerpTime(lerpTime), _minHeight(_transform.position.y)
    {

        //_playerPositions
        const std::list<std::unique_ptr<ECS::Entity>>& entities = ECS::Coordinator::GetInstance()->GetEntities();

        for (auto it = entities.begin(); it != entities.end(); it++) {
            if (it->get()->GetTag() != "Player")
                continue;
            if (it->get()->HasComponent<Transform>()) {
                Transform& transform = it->get()->GetComponent<Transform>();
                _playerPositions.push_back(transform.position);
            }
        }
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
        RayLib::Vector3 positionsAverage = GetAveragePosition();

        //camera.SetPosition(_targetLookAt + _transform.position);
        //camera.SetTarget(_targetLookAt);

        camera.SetPosition(positionsAverage + _transform.position);
        camera.SetTarget(positionsAverage);


        camera.Update();
    }

    void Camera::LerpToPos(RayLib::Vector3 position, float lerp)
    {
        _transform.position = position;
        _lerpTime = lerp;
    }

    RayLib::Vector3 Camera::GetAveragePosition()
    {
        RayLib::Vector3 sum;
        RayLib::Vector3 result;

        for (auto it = _playerPositions.begin(); it != _playerPositions.end(); it++) {
            // if one of the players are off camera, min threshold + 1
            //if (::GetWorldToScreen(it->get(), camera.GetCamera()).x > RayLib::Window::GetInstance(0.0f, "")->GetSize().x) {
            //    _transform.position.y += 1;
            //}
            //if (::GetWorldToScreen(it->get(), camera.GetCamera()).y > RayLib::Window::GetInstance(0.0f, "")->GetSize().y) {
            //    _transform.position.y += 1;
            //}
            sum += it->get();
        }
        result = sum / static_cast<float>(_playerPositions.size());
        return (result);
    }

}