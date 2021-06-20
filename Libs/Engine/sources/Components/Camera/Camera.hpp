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
#include "Coordinator.hpp"
#include "Sound.hpp"

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
            Camera(ECS::Entity& attatched, RayLib::Camera3D& camera, float lerpTime = 0.1f);

            /**
             * @brief Construct a new Camera object
             * 
             * @param attatched 
             * @param camera 
             * @param musicPath 
             * @param lerpTime 
             */
            Camera(ECS::Entity& attatched, RayLib::Camera3D& camera, const std::string& musicPath, float lerpTime = 0.1f);

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
             * @brief Set target position and lerpspeed
             * 
             * @param position 
             * @param lerp 
             */
            void LerpToPos(RayLib::Vector3 position, float lerp=0.1f);

            /**
             * @brief Camera
             * 
             */
            RayLib::Camera3D& camera;

            std::ostream &operator<<(std::ostream &os) override {return os;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

            /**
             * @brief Get the Average Position of all players/AI
             * 
             * @return RayLib::Vector3 
             */
            RayLib::Vector3 GetAveragePosition();

            /**
             * @brief Returns true if the position is beyond window size - margin
             * 
             * @param position 
             * @param margin 
             * @param windowSize 
             * @return true 
             * @return false 
             */
            bool IsPositionOffScreen(Vector3 position, RayLib::Vector2<int> margin, RayLib::Vector2<int> windowSize);

            /**
             * @brief Get the Main Camera object
             * 
             * @return Camera& 
             */
            static Camera& GetMainCamera();

            /**
             * @brief Get the Entity object
             * 
             * @return ECS::Entity& 
             */
            ECS::Entity& GetEntity();

        protected:
        private:
            /**
             * @brief Attatched entity
             * 
             */
            ECS::Entity& _entity;
            /**
             * @brief Camera's transform
             * 
             */
            Transform& _transform;
            /**
             * @brief time variable for interpolation
             * 
             */
            float _lerpTime;
            /**
             * @brief Minimum height for zoom/dezoom
             * 
             */
            float _minHeight;

            std::shared_ptr<RayLib::Sound> _music;

    };
}

#endif /* !CAMERA_HPP_ */
