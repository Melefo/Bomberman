/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** SpeedBoost
*/

#ifndef SPEEDBOOST_HPP_
#define SPEEDBOOST_HPP_

#include "APickUp.hpp"
#include "AController.hpp"
#include "PlayerInputs.hpp"

namespace Component
{
    class SpeedBoost : public APickUp {
        public:
            /**
             * @brief Construct a new Speed Boost object
             * 
             * @param entity 
             * @param pickUpRadius 
             */
            SpeedBoost(ECS::Entity& entity, float pickUpRadius=2.0f);
            /**
             * @brief Destroy the Speed Boost object
             * 
             */
            ~SpeedBoost() override = default;
            /**
             * @brief Construct a new Speed Boost object
             * 
             * @param other 
             */
            SpeedBoost(const SpeedBoost& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return SpeedBoost& 
             */
            SpeedBoost& operator=(const SpeedBoost& other) = default;

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
            void ApplyBoost(AController& acontroller);

            /**
             * @brief Called every frame, can be used for debug here
             * 
             * @param dt 
             * @param entity 
             */
            void Update(double dt, ECS::Entity& entity) override;
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

#endif /* !SPEEDBOOST_HPP_ */
