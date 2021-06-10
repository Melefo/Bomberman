/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** APickUp
*/

#ifndef APICKUP_HPP_
#define APICKUP_HPP_

#include "IBehaviour.hpp"
#include "Collider.hpp"

namespace Component
{
    class APickUp : public IBehaviour {
        public:
            APickUp(ECS::Entity& entity);
            ~APickUp() = default;


            virtual void OnPickup(ECS::Entity& collision) = 0;

            /**
             * @brief Called every frame
             * 
             * @param dt 
             * @param entity 
             */
            virtual void Update(double dt, ECS::Entity& entity) = 0;
            /**
             * @brief Check collision, call OnPickup
             * 
             * @param entity 
             */
            void FixedUpdate(ECS::Entity& entity) override;
            virtual void LateUpdate(double dt, ECS::Entity& entity) = 0;

        protected:
            ECS::Entity& _entity;
        private:
    };
}

#endif /* !APICKUP_HPP_ */
