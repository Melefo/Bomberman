/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Camera
*/

#include "Camera.hpp"
#include <iostream>
#include "Window.hpp"
#include "Exceptions.hpp"

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
        //std::cout << "Camera position: " << _transform.position << std::endl;
    }

    void Camera::FixedUpdate(ECS::Entity&)
    {

    }

    void Camera::LateUpdate(double, ECS::Entity&)
    {
        const RayLib::Vector3 pos = camera.GetPosition();
        RayLib::Vector3 positionsAverage = GetAveragePosition();

        if (positionsAverage != RayLib::Vector3()) {
            // lerp targets
            const RayLib::Vector3 currentTarget = camera.GetTarget();
            RayLib::Vector3 lerp = currentTarget;
            lerp.Lerp(positionsAverage, 0.05f);
            camera.SetTarget(lerp);

            // uncomment for a cool effect on startup, also fixes most stuttering
            RayLib::Vector3 lerpPos = pos;
            lerpPos.Lerp(positionsAverage + _transform.position, 0.25f);
            camera.SetPosition(lerpPos);
        } else {
            camera.SetPosition(_transform.position);
        }
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

        //! mettre à jour la liste des players si yen a qui perd
        RayLib::Vector2<int> margin = RayLib::Vector2<int>(10, 10);
        RayLib::Vector2<int> windowSize = RayLib::Window::GetInstance(0.0f, "")->GetSize();
        bool offscreen = false;
        int extraSpace = 0;

        for (auto it = _playerPositions.begin(); it != _playerPositions.end(); it++) {
            // if one of the players are off camera, min threshold + 1
            if (IsPositionOffScreen(it->get(), margin, windowSize))
                offscreen = true;

            if (IsPositionOffScreen(it->get(), margin * 2, windowSize))
                extraSpace += 1;

            sum += it->get();
        }

        if (offscreen)
            _transform.position.y += 1.0f;
        else if (extraSpace == _playerPositions.size() && _transform.position.y > _minHeight)
            _transform.position.y -= 1.0f;

        if (sum != RayLib::Vector3())
            result = sum / static_cast<float>(_playerPositions.size());
        return (result);
    }

    bool Camera::IsPositionOffScreen(Vector3 position, RayLib::Vector2<int> margin, RayLib::Vector2<int> windowSize)
    {
        RayLib::Vector2<int> screenPos = camera.GetWorldToScreen(position);

        if (screenPos.x > windowSize.x - margin.x)
            return (true);
        if (screenPos.x < margin.x)
            return (true);
        if (screenPos.y > windowSize.y - margin.y)
            return (true);
        if (screenPos.y < margin.y)
            return (true);
        return (false);
    }

    Camera& Camera::GetMainCamera()
    {
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        const std::list<std::unique_ptr<ECS::Entity>>& entities = coordinator->GetEntities();

        for (auto entity = entities.begin(); entity != entities.end(); entity++) {
            if (entity->get()->HasComponent<Camera>()) {
                return (entity->get()->GetComponent<Camera>());
            }
        }
        throw ECS::Exception::ComponentException("There is no camera in the scene");
    }


}