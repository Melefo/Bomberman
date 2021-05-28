/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** UISystem
*/

#ifndef UISYSTEM_HPP_
#define UISYSTEM_HPP_

#include "ASystem.hpp"
#include "Entity.hpp"

namespace Prototype
{
    class UISystem : public ECS::ASystem {
        public:
            UISystem();
            ~UISystem() override = default;

            void Update(double dt, ECS::Entity &entity) override;

        protected:
        private:
    };
}

#endif /* !UISYSTEM_HPP_ */
