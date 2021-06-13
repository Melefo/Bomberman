/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** CoolDownBoost
*/

#ifndef COOLDOWNBOOST_HPP_
#define COOLDOWNBOOST_HPP_

#include "APickUp.hpp"
#include "AController.hpp"
#include "DropBomb.hpp"
#include "GameConfiguration.hpp"
#include "PlayerInputs.hpp"

namespace Component
{
    class CoolDownBoost : public APickUp {
        public:
            /**
             * @brief Construct a new Cool Down Boost object
             * 
             * @param entity 
             * @param pickUpRadius 
             */
            CoolDownBoost(ECS::Entity& entity, float pickUpRadius=2.0f);
            /**
             * @brief Destroy the Cool Down Boost object
             * 
             */
            ~CoolDownBoost() override = default;
            /**
             * @brief Construct a new Cool Down Boost object
             * 
             * @param other 
             */
            CoolDownBoost(const CoolDownBoost& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return CoolDownBoost& 
             */
            CoolDownBoost& operator=(const CoolDownBoost& other) = default;

            /**
             * @brief Pickup effect, called when someone walks on me
             * 
             * @param collision 
             */
            void OnPickup(ECS::Entity& collision) override;

            /**
             * @brief Applies a speed boost to Acontroller component
             * 
             * @param acontroller 
             */
            void DecrementCooldown(AController& acontroller);

            /**
             * @brief Called after update
             * 
             * @param dt 
             * @param entity 
             */
            void LateUpdate(double dt, ECS::Entity& entity) override;

            std::ostream &operator<<(std::ostream &os) override {return os;};
            std::istream &operator>>(std::istream &is) override {return is;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

        protected:
        private:
    };
}

#endif /* !COOLDOWNBOOST_HPP_ */
