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
            std::istream &operator>>(std::istream &is) override {return is;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

            RayLib::Vector3 GetAveragePosition();

            static Camera& GetMainCamera();

        protected:
        private:
            ECS::Entity& _entity;
            Transform& _transform;
            std::vector<std::reference_wrapper<RayLib::Vector3>> _playerPositions;
            float _lerpTime;
            float _minHeight;

    };
}

#endif /* !CAMERA_HPP_ */
