/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Camera
*/

#include "Camera.hpp"

namespace Component
{
    Camera::Camera(RayLib::Camera3D startCamera)
    {
        camera = startCamera;
    }

    std::ostream& Camera::operator<<(std::ostream& stream)
    {
        // save camera parameters
        // target transform
        return (stream);
    }
}