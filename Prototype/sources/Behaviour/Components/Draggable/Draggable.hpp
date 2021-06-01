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
#include "Physics3D.hpp"
#include <cmath>

namespace Prototype
{
    class Draggable : public IBehaviour {
        public:
            Draggable(ECS::Entity& attatchedEntity, RayLib::Camera3D& camera);
            ~Draggable() = default;

            void Update(float dt) override;

        protected:
        private:
            std::vector<std::reference_wrapper<Collider>> _colliders;
            ECS::Entity& _entity;
            RayLib::Camera3D& _camera;
            bool _selected;
            Transform& _transform;

    };
}

#endif /* !DRAGGABLE_HPP_ */
