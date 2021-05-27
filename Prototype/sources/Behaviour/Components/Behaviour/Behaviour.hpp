/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Behaviour
*/

#ifndef BEHAVIOUR_HPP_
#define BEHAVIOUR_HPP_

#include "IComponent.hpp"
#include "Entity.hpp"

namespace Prototype
{
    class Behaviour : public ECS::IComponent {
        public:
            Behaviour() = default;
            ~Behaviour() override = default;

            virtual void Update(float dt);

        protected:
        private:

    };
}

#endif /* !BEHAVIOUR_HPP_ */
