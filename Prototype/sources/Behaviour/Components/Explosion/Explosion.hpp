/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Explosion
*/

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include <cinttypes>
#include "IComponent.hpp"
#include "Vector3.hpp"
#include "IBehaviour.hpp"
#include "Window.hpp"
#include "CollisionSystem.hpp"
#include "Transform.hpp"
#include "Destructible.hpp"
#include "Exceptions.hpp"

namespace Prototype
{
    class Explosion : public IBehaviour {
        public:
            enum class ExplosionType
            {
                CIRCLE,
                CROSS,
                VERTICAL,
                HORIZONTAL,
            };
            Explosion(ECS::Entity& entity, float radius=1.0f,
                      Explosion::ExplosionType type=Explosion::ExplosionType::CROSS,
                      unsigned int power=1,
                      float timer=3.0f);

            ~Explosion() override = default;

            void Update(float dt) override;
            void FixedUpdate(ECS::Entity& entity) override;

            Explosion::ExplosionType type;
            unsigned int power;
        protected:
        private:
            float _radius;
            float _explosionTimer;
            std::unique_ptr<RayLib::Window>& _window;
            ECS::Entity& _myEntity;
            Transform& _transform;
    };
}

#endif /* !EXPLOSION_HPP_ */
