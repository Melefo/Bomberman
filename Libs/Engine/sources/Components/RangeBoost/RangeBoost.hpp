/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RangeBoost
*/

#ifndef RANGEBOOST_HPP_
#define RANGEBOOST_HPP_

#include "APickUp.hpp"
#include "AController.hpp"
#include "DropBomb.hpp"
#include "GameConfiguration.hpp"
#include "PlayerInputs.hpp"

namespace Component
{
    class RangeBoost : public APickUp {
        public:
            /**
             * @brief Construct a new Range Boost object
             * 
             * @param entity 
             * @param pickUpRadius 
             */
            RangeBoost(ECS::Entity& entity, float pickUpRadius=2.0f);
            /**
             * @brief Destroy the Range Boost object
             * 
             */
            ~RangeBoost() override = default;
            /**
             * @brief Construct a new Range Boost object
             * 
             * @param other 
             */
            RangeBoost(const RangeBoost& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return RangeBoost& 
             */
            RangeBoost& operator=(const RangeBoost& other) = default;

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
            void IncrementRange(AController& acontroller);

            /**
             * @brief Called after update
             * 
             * @param dt 
             * @param entity 
             */
            void LateUpdate(double dt, ECS::Entity& entity) override;

            std::ostream &operator<<(std::ostream &os) override {return os;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};
        protected:
        private:
            int getPlayerNbr(const std::string &tag);
    };
}

#endif /* !RANGEBOOST_HPP_ */
