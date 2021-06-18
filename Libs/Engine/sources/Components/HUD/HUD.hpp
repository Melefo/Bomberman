/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** HUD
*/

#ifndef HUD_HPP_
#define HUD_HPP_

#include "IComponent.hpp"
#include "Entity.hpp"
#include "AController.hpp"

namespace Component
{
    /**
     * @brief HUD base component class
     * 
     */
    class HUD : public IBehaviour {
        public:
            /**
             * @brief Construct a new HUD object
             * 
             * @param attatchedEntity
             * @param playerNbr
             */
            HUD(Component::AController &attatchedController, int playerNbr);
            /**
             * @brief Destroy the HUD object
             * 
             */
            ~HUD() = default;
            /**
             * @brief Construct a new HUD object
             * 
             * @param other 
             */
            HUD(const HUD& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return HUD& 
             */
            HUD& operator=(const HUD& other) = default;

            /**
             * @brief Get the offset of the hud part
             * 
             * @return Raylib::Vector3 offset
             * 
             */
            RayLib::Vector3 &getOffset();

            /**
             * @brief Get the AController of the hud part
             * 
             * @return Component::AController &_myAController
             * 
             */
            Component::AController &getAController();

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
             * @brief Reference to attatched AController
             * 
             */
            Component::AController &_myAController;

            /**
             * @brief Offset to know where to draw things
             * 
             */
            RayLib::Vector3 _offset;

        private:
    };
}

#endif /* !HUD_HPP_ */
