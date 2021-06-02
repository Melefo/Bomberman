/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** DropBomb
*/

#ifndef DROPBOMB_HPP_
#define DROPBOMB_HPP_

#include "IBehaviour.hpp"
#include "Input.hpp"
#include "PhysicsBody.hpp"
#include "Entity.hpp"
#include "Collider.hpp"
#include "Explosion.hpp"
#include "BoxCollider.hpp"
#include "Transform.hpp"
#include "Renderer.hpp"
#include "Window.hpp"

namespace Prototype
{
    class DropBomb : public IBehaviour {
        public:
            // ? prendre en parametre un std::function à appeler lorsqu'on clique sur dropKey ?
            DropBomb(ECS::Entity& attatchedEntity, ECS::Coordinator& coordinator, int dropBombKey=KEY_X, float dropDelay=2.5f);
            ~DropBomb() override = default;

            // ! à mettre dans une factory
            // instantiate bomb
            void InstantiateBomb(RayLib::Vector3 position,
                                 Explosion::ExplosionType explosionType=Explosion::ExplosionType::CIRCLE,
                                 RayLib::Vector3 radius=RayLib::Vector3(1.0f, 1.0f, 1.0f));

            void Update(float dt) override;
            void FixedUpdate(ECS::Entity& entity) override;

        protected:
        private:
            RayLib::Input _input;
            ECS::Entity& _entity;
            ECS::Coordinator& _coordinator;
            Transform& _transform;
            int _bombKey;
            float _dropDelay;
            float _timeToDrop;
            std::unique_ptr<RayLib::Window>& _window;
    };
}

#endif /* !DROPBOMB_HPP_ */
