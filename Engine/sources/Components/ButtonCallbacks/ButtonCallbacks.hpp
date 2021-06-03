/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** ButtonCallbacks
*/

#ifndef BUTTONCALLBACKS_HPP_
#define BUTTONCALLBACKS_HPP_

#include "IComponent.hpp"
#include "Entity.hpp"
#include "IBehaviour.hpp"
#include "Button.hpp"
#include <iostream>

namespace Component
{
    class ButtonCallbacks : public IBehaviour {
        public:
            ButtonCallbacks(ECS::Entity& attatchedEntity);
            ~ButtonCallbacks() override = default;

            void Update(double dt) override;
            void FixedUpdate(ECS::Entity& entity) override;
            void SayHello(void);

        protected:
        private:
            ECS::Entity& _entity;
            Button& _button;
    };
}

#endif /* !BUTTONCALLBACKS_HPP_ */
