/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Destructible
*/

#ifndef DESTRUCTIBLE_HPP_
#define DESTRUCTIBLE_HPP_

#include <cinttypes>
#include "IComponent.hpp"
#include "Vector3.hpp"
#include "Entity.hpp"

namespace Component
{
    /**
     * @brief Component allowing for entities to be destructible
     * 
     */
    class Destructible : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Destructible component
             * 
             * @param entity ref to attatched Entity
             * @param resistance amount of damage sustained before destruction
             */
            Destructible(ECS::Entity& entity, int resistance=1);
            /**
             * @brief Destroy the Destructible component
             * 
             */
            ~Destructible() override = default;
            /**
             * @brief Construct a new Destructible object
             * 
             * @param other 
             */
            Destructible(const Destructible& other) = default;
            /**
             * @brief Assigment operator
             * 
             * @param other 
             * @return Destructible& 
             */
            Destructible& operator=(const Destructible& other) = default;

            /**
             * @brief Get the Resistance
             * 
             * @return int 
             */
            int GetResistance();

            /**
             * @brief Inflict some damage
             * 
             * @param damage 
             */
            void TakeDamage(int damage);

            std::ostream &operator<<(std::ostream &os) override;
            std::istream &operator>>(std::istream &is) override;
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override;

        protected:
        private:
            ECS::Entity& _myEntity;
            int _resistance;
    };
}

#endif /* !DESTRUCTIBLE_HPP_ */