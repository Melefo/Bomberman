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

namespace Prototype
{
    class Explosion : public ECS::IComponent {
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
                      unsigned int power=1);
            ~Explosion() override = default;

            RayLib::Vector3 radius;
            Explosion::ExplosionType type;
            unsigned int power;
        protected:
        private:
    };
}

#endif /* !EXPLOSION_HPP_ */
