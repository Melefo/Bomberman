/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** IBehaviour
*/

#ifndef IBEHAVIOUR_HPP_
#define IBEHAVIOUR_HPP_

#include "IComponent.hpp"
#include "Entity.hpp"

namespace Prototype
{
    class IBehaviour : public ECS::IComponent {
        public:
            IBehaviour() = default;
            virtual ~IBehaviour() = default;

            virtual void Update(float dt) = 0;
            virtual void FixedUpdate(ECS::Entity& entity) = 0;

        protected:
        private:

    };
}

#endif /* !IBEHAVIOUR_HPP_ */
