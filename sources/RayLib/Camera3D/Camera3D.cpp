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
        camera.position = position.getVector3(); // Camera position
        camera.target = target.getVector3();     // Camera looking at point
        camera.up = up.getVector3();             // Camera up vector (rotation towards target)
        camera.fovy = fovy;                      // Camera field-of-view Y
        camera.projection = projection;          // Camera mode type
    }

    Camera3D::~Camera3D()
    {

    }

    void Camera3D::BeginMode()
    {
        ::BeginMode3D(camera);
    }

    void Camera3D::EndMode()
    {
        ::EndMode3D();
    }

    void Camera3D::SetCameraMode(int mode)
    {
        ::SetCameraMode(camera, mode);
    }
}

