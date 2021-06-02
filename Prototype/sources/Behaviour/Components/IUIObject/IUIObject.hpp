/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** IUIObject
*/

#ifndef IUIOBJECT_HPP_
#define IUIOBJECT_HPP_

#include "IComponent.hpp"
#include "Vector2.hpp"

namespace Prototype
{
    class IUIObject : public ECS::IComponent {
        public:
            IUIObject() = default;
            ~IUIObject() override = default;

            virtual void Draw(RayLib::Vector2<float> position, RayLib::Vector2<float> scale=RayLib::Vector2<float>(1.0f, 1.0f)) = 0;

        protected:
        private:
    };
}

#endif /* !IUIOBJECT_HPP_ */
