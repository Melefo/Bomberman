/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** SphereCollider
*/

#ifndef SPHERECOLLIDER_HPP_
#define SPHERECOLLIDER_HPP_

#include <cinttypes>
#include "IComponent.hpp"
#include "Vector3.hpp"
#include "Collider.hpp"
#include "Physics3D.hpp"
#include "Transform.hpp"
#include "Window.hpp"

namespace Component
{
    class SphereCollider : public Collider {
        public:
            /**
             * @brief Construct a new Sphere Collider object
             * 
             * @param entity 
             * @param center 
             * @param radius 
             */
            SphereCollider(ECS::Entity& entity, RayLib::Vector3 center, float radius);
            /**
             * @brief Destroy the Sphere Collider object
             * 
             */
            ~SphereCollider() = default;
            /**
             * @brief Construct a new Sphere Collider object
             * 
             * @param other 
             */
            SphereCollider(const SphereCollider& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return SphereCollider& 
             */
            SphereCollider& operator=(const SphereCollider& other) = default;

            /**
             * @brief Returns true if colliding with another entity
             * 
             * @return true 
             * @return false 
             */
            bool IsColliding() override;
            /**
             * @brief Returns true if colliding with sphere
             * 
             * @param center 
             * @param radius 
             * @return true 
             * @return false 
             */
            bool CheckCollision(RayLib::Vector3 center, float radius) override;
            /**
             * @brief Returns true if colliding with box
             * 
             * @param box 
             * @return true 
             * @return false 
             */
            bool CheckCollision(RayLib::BoundingBox& box) override;
            /**
             * @brief Returns true if colliding with ray
             * 
             * @param ray 
             * @return true 
             * @return false 
             */
            bool CheckCollision(RayLib::Ray& ray) override;
            /**
             * @brief Returns true if colliding with anything, at position
             * 
             * @param center 
             * @return true 
             * @return false 
             */
            bool IsCollidingAtPosition(RayLib::Vector3 center) override;
            /**
             * @brief Debug, draw lines
             * 
             */
            void DrawLines() override;
            /**
             * @brief Update the position, relative to attatched transform
             * 
             */
            void UpdatePosition();
            /**
             * @brief Get the colliding entity
             * 
             * @return ECS::Entity& 
             */
            ECS::Entity& GetCollision() override;

            std::ostream &operator<<(std::ostream &os) override {return os;};
            std::istream &operator>>(std::istream &is) override {return is;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

        protected:
        private:
            /**
             * @brief Sphere center
             * 
             */
            RayLib::Vector3 _center;
            /**
             * @brief Radius of sphere
             * 
             */
            float _radius;
            /**
             * @brief Attatched transform
             * 
             */
            Transform& _transform;
    };
}

#endif /* !SPHERECOLLIDER_HPP_ */
