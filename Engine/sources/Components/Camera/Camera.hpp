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
#include "Entity.hpp"
#include "Transform.hpp"
#include "IBehaviour.hpp"

namespace Component
{
    /**
     * @brief Camera component
     * 
     */
    class Camera : public Component::IBehaviour {
        public:
            /**
             * @brief Construct a new Camera object
             * 
             * @param camera 
             */
            Camera(ECS::Entity& attatched, RayLib::Camera3D& camera, Transform& target);
            // todo take target lookat
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

            void Update(double dt, ECS::Entity& entity) override;
            void FixedUpdate(ECS::Entity& entity) override;
            void LateUpdate(double dt, ECS::Entity& entity) override;

            /**
             * @brief Camera
             * 
             */
            RayLib::Camera3D& camera;

            // !set lerp position (take pos and speed)

        protected:
        private:
            ECS::Entity& _entity;
            Component::Transform& _transform;
            Component::Transform& _targetLookat;

    };
}

#endif /* !CAMERA_HPP_ */
