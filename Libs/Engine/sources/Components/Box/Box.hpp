/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Box
*/

#ifndef BOX_HPP_
#define BOX_HPP_

#include "Destructible.hpp"
#include "Coordinator.hpp"
#include "Camera.hpp"
//#include "EntityFactory.hpp"

namespace Component
{
    class Box : public Destructible {
        public:
            Box(ECS::Entity& entity, int resistance=1, float lootChance=0.1f);
            ~Box() override = default;

            void TakeDamage(int damage) override;

            void SpawnLoot(void);

        protected:
        private:
            float _lootChance;
    };
}

#endif /* !BOX_HPP_ */
