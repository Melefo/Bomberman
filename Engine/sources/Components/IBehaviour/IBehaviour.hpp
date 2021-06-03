/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1indiestudio-victor.trencic
** File description:
** IBehaviour
*/

#ifndef IBEHAVIOUR_HPP_
#define IBEHAVIOUR_HPP_

#include "IComponent.hpp"
#include "Entity.hpp"

namespace Component
{
    /**
     * @brief IBehaviour base component (CF Monobehaviour class in Unity)
     * 
     */
    class IBehaviour : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new IBehaviour object
             * 
             */
            IBehaviour() = default;
            /**
             * @brief Destroy the IBehaviour object
             * 
             */
            virtual ~IBehaviour() = default;
            /**
             * @brief Construct a new IBehaviour object
             * 
             * @param other 
             */
            IBehaviour(const IBehaviour& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return IBehaviour& 
             */
            IBehaviour& operator=(const IBehaviour& other) = default;

            /**
             * @brief Called once per cpu update
             * 
             * @param dt Time since last call to update
             */
            virtual void Update(double dt) = 0;
            /**
             * @brief Called every fixed seconds (CF coordinator)
             * 
             * @param entity 
             */
            virtual void FixedUpdate(ECS::Entity& entity) = 0;

        protected:
        private:

    };
}

#endif /* !IBEHAVIOUR_HPP_ */
