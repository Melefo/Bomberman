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

class EntityFactory;

namespace Component
{
    class Box : public Destructible {
        public:
            /**
             * @brief Construct a new Box object
             * 
             * @param entity 
             * @param resistance 
             * @param lootChance 
             */
            Box(ECS::Entity& entity, int resistance=1, float lootChance=0.1f);
            /**
             * @brief Destroy the Box object
             * 
             */
            ~Box() override = default;
            /**
             * @brief Construct a new Box object
             * 
             * @param other 
             */
            Box(const Box& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return Box& 
             */
            Box& operator=(const Box& other) = default;

            /**
             * @brief 
             * 
             * @param damage 
             */
            void TakeDamage(int damage) override;

            /**
             * @brief 
             * 
             */
            void SpawnLoot(void);

            std::ostream &operator<<(std::ostream &os) override;
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override;

        protected:
        private:
            float _lootChance;
    };
}

#endif /* !BOX_HPP_ */
