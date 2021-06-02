/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "IComponent.hpp"
#include "Vector3.hpp"
#include "Camera3D.hpp"

namespace Component
{
    class Camera : public ECS::IComponent {
        public:
            Camera(RayLib::Camera3D camera=RayLib::Camera3D());
            ~Camera() override = default;

            RayLib::Camera3D camera;
        protected:
        private:
    };
}

#endif /* !CAMERA_HPP_ */
