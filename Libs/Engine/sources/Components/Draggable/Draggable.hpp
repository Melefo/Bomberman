/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Draggable
*/

#ifndef DRAGGABLE_HPP_
#define DRAGGABLE_HPP_

#include "IBehaviour.hpp"
#include "Input.hpp"
#include "PhysicsBody.hpp"
#include "Entity.hpp"
#include "Collider.hpp"
#include "Camera3D.hpp"
#include "Mouse.hpp"
#include "Transform.hpp"
#include <cmath>

namespace Component
{
    /**
     * @brief Draggable component (allows for objects to be selected and dragged with the mouse)
     * 
     */
    class Draggable : public IBehaviour {
        public:
            /**
             * @brief Construct a new Draggable object
             * 
             * @param attatchedEntity required to get a list of attatched colliders
             * @param camera required to construct a mouse raycast
             */
            Draggable(ECS::Entity& attatchedEntity, RayLib::Camera3D& camera);
            /**
             * @brief Destroy the Draggable object
             * 
             */
            ~Draggable() override = default;
            /**
             * @brief Construct a new Draggable object
             * 
             * @param other 
             */
            Draggable(const Draggable& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return Draggable& 
             */
            Draggable& operator=(const Draggable& other) = default;

            /**
             * @brief Checks if the mouse ray collides with colliders, selects/moves the transform
             * 
             * @param dt 
             */
            void Update(double dt, ECS::Entity& entity) override;
            /**
             * @brief 
             * 
             * @param entity 
             */
            void FixedUpdate(ECS::Entity& entity) override;

            /**
             * @brief 
             * 
             * @param dt 
             * @param entity 
             */
            void LateUpdate(double dt, ECS::Entity& entity) override;

            std::ostream &operator<<(std::ostream &os) override {return os;};
            std::istream &operator>>(std::istream &is) override {return is;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};


        protected:
        private:
            /**
             * @brief vector of colliders to test mouse selection
             * 
             */
            std::vector<std::reference_wrapper<Collider>> _colliders;
            /**
             * @brief Attatched entity to modify transform position
             * 
             */
            ECS::Entity& _entity;
            /**
             * @brief Camera to get the mouse raycast
             * 
             */
            RayLib::Camera3D& _camera;
            /**
             * @brief If selected -> move with mouse
             * 
             */
            bool _selected;
            /**
             * @brief Reference to transform component, to avoid constant get calls
             * 
             */
            Transform& _transform;

    };
}

#endif /* !DRAGGABLE_HPP_ */
