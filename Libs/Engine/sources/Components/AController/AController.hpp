/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AController
*/

#ifndef ACONTROLLER_HPP_
#define ACONTROLLER_HPP_

#include "IBehaviour.hpp"
#include "Movement.hpp"
#include "DropBomb.hpp"

namespace Component
{
    class AController : public IBehaviour {
        public:
            /**
             * @brief Construct a new AController object
             * 
             * @param attatchedEntity 
             * @param speed 
             * @param dropDelay 
             */
            AController(ECS::Entity& attatchedEntity, float speed=0.5f, float dropDelay=2.5f);
            /**
             * @brief Destroy the AController object
             * 
             */
            ~AController() = default;
            /**
             * @brief Construct a new AController object
             * 
             * @param other 
             */
            AController(const AController& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return AController& 
             */
            AController& operator=(const AController& other) = default;

            /**
             * @brief Get the Movement object
             * 
             * @return Component::Movement& 
             */
            Component::Movement& GetMovement();
            /**
             * @brief Get the Drop Bomb object
             * 
             * @return Component::DropBomb& 
             */
            Component::DropBomb& GetDropBomb();

            /**
             * @brief Get the AController
             * 
             * @return 
             * 
             */
            Component::AController &GetAController();

            /**
             * @brief Called every frame
             * To be overridden by a playercontroller or AI controller
             * @param dt 
             * @param entity 
             */
            virtual void Update(double dt, ECS::Entity& entity) = 0;
            /**
             * @brief Called every ~0.02 seconds
             * To be overridden by a playercontroller or AI controller
             * @param entity 
             */
            virtual void FixedUpdate(ECS::Entity& entity) = 0;
            /**
             * @brief Called after update
             * To be overridden by a playercontroller or AI controller
             * @param dt 
             * @param entity 
             */
            virtual void LateUpdate(double dt, ECS::Entity& entity) = 0;

        protected:
            /**
             * @brief movement behaviour
             * 
             */
            Component::Movement _movement;
            /**
             * @brief Dropbomb component
             * 
             */
            Component::DropBomb _dropBomb;
        private:
    };
}

#endif /* !ACONTROLLER_HPP_ */
