/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsSystem
*/

#ifndef PHYSICSSYSTEM_HPP_
#define PHYSICSSYSTEM_HPP_

#include "ASystem.hpp"
#include "Entity.hpp"

namespace Component
{
    class PhysicsSystem : public ECS::ASystem {
        public:
            PhysicsSystem();
            ~PhysicsSystem() override = default;

            void Update(double dt, ECS::Entity &entity) override;

        protected:
        private:
    };
}

#endif /* !PHYSICSSYSTEM_HPP_ */
