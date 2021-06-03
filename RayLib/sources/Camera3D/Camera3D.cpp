/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Camera3D
*/

#include "Camera3D.hpp"

namespace RayLib
{
    Camera3D::Camera3D(Vector3 position, Vector3 target, Vector3 up, float fovy, int projection)
    {
        _camera.position = position.getVector3(); // Camera position
        _camera.target = target.getVector3();     // Camera looking at point
        _camera.up = up.getVector3();             // Camera up vector (rotation towards target)
        _camera.fovy = fovy;                      // Camera field-of-view Y
        _camera.projection = projection;          // Camera mode type
    }

    Camera3D::~Camera3D()
    {

    }

    void Camera3D::Update()
    {
        ::UpdateCamera(&_camera);
    }

    void Camera3D::BeginMode()
    {
        ::BeginMode3D(_camera);
    }

    void Camera3D::EndMode()
    {
        ::EndMode3D();
    }

    void Camera3D::SetCameraMode(int mode)
    {
        ::SetCameraMode(_camera, mode);
    }

    Ray Camera3D::GetMouseRay(Vector2<float> mousePos)
    {
        Ray ray(::GetMouseRay(mousePos.getVector2(), _camera));

        return (ray);
    }

    ::Camera3D Camera3D::GetCamera()
    {
        return (_camera);
    }

}

