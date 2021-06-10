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
            AController(ECS::Entity& attatchedEntity, float speed=0.5f, float dropDelay=2.5f);
            ~AController() = default;

            Component::Movement& GetMovement();
            Component::DropBomb& GetDropBomb();

            virtual void Update(double dt, ECS::Entity& entity) = 0;
            virtual void FixedUpdate(ECS::Entity& entity) = 0;
            virtual void LateUpdate(double dt, ECS::Entity& entity) = 0;

        protected:
            Component::Movement _movement;
            Component::DropBomb _dropBomb;
        private:
    };
}

#endif /* !ACONTROLLER_HPP_ */
