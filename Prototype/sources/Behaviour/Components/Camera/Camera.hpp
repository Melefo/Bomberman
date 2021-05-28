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

namespace Prototype
{
    class Camera : public ECS::IComponent {
        public:
            Camera(Raylib::Camera3D camera=Raylib::Camera3D());
            ~Camera() override = default;

            Raylib::Camera3D camera;
        protected:
        private:
    };
}

#endif /* !CAMERA_HPP_ */
