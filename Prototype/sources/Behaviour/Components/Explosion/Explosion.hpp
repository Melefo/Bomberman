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
            Explosion(RayLib::Vector3 radius=RayLib::Vector3(),
                      Explosion::ExplosionType type=Explosion::ExplosionType::CROSS,
                      unsigned int power=1,
                      float timer=3.0f);

            ~Explosion() override = default;

            void Update(float dt) override;
            void FixedUpdate(ECS::Entity& entity) override;

            RayLib::Vector3 radius;
            Explosion::ExplosionType type;
            unsigned int power;
        protected:
        private:
            float _explosionTimer;
            std::unique_ptr<RayLib::Window>& _window;

    };
}

#endif /* !EXPLOSION_HPP_ */
