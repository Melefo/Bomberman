/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Circle
*/

#ifndef CIRCLE_HPP_
#define CIRCLE_HPP_

#include <raylib.h>
#include "Vector2.hpp"

namespace RayLib
{
    class Circle {
        public:
            Circle(RayLib::Vector2<float> center, float radius);
            ~Circle() = default;

            void SetRadius(float radius);
            RayLib::Vector2<float> GetCenter(void);
            float GetRadius(void);
            void SetCenter(RayLib::Vector2<float> center);

        protected:
        private:
            RayLib::Vector2<float> _center;
            float _radius;
    };
}

#endif /* !CIRCLE_HPP_ */
