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
    /**
     * @brief Camera component
     * 
     */
    class Camera : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Camera object
             * 
             * @param camera 
             */
            Camera(RayLib::Camera3D camera=RayLib::Camera3D());
            /**
             * @brief Destroy the Camera object
             * 
             */
            ~Camera() override = default;
            /**
             * @brief Construct a new Camera object
             * 
             * @param other 
             */
            Camera(const Camera& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return Camera& 
             */
            Camera& operator=(const Camera& other) = default;

            /**
             * @brief Camera
             * 
             */
            RayLib::Camera3D camera;

            std::ostream& operator<<(std::ostream& stream) override;

        protected:
        private:
    };
}

#endif /* !CAMERA_HPP_ */
