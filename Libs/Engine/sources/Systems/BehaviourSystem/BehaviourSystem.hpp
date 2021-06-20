/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** BehaviourSystem
*/

#ifndef BEHAVIOURSYSTEM_HPP_
#define BEHAVIOURSYSTEM_HPP_

#include "ASystem.hpp"
#include "Entity.hpp"
#include "IBehaviour.hpp"
#include "AController.hpp"

namespace Component
{
    class BehaviourSystem : public ECS::ASystem {
        public:
            /**
             * @brief Construct a new Behaviour System object
             * 
             */
            BehaviourSystem();
            /**
             * @brief Destroy the Behaviour System object
             * 
             */
            ~BehaviourSystem() override = default;
            /**
             * @brief Construct a new Behaviour System object
             * 
             * @param other 
             */
            BehaviourSystem(const BehaviourSystem& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return BehaviourSystem& 
             */
            BehaviourSystem& operator=(const BehaviourSystem& other) = default;

            void Update(double dt, ECS::Entity &entity) override;
            void FixedUpdate(ECS::Entity &entity) override;
            void LateUpdate(double dt, ECS::Entity &entity) override;

        protected:
        private:
    };
}

#endif /* !BEHAVIOURSYSTEM_HPP_ */
