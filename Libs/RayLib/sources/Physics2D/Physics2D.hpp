/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Physics2D
*/

#ifndef PHYSICS2D_HPP_
#define PHYSICS2D_HPP_

#include <raylib.h>
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"

namespace RayLib
{
    class Physics2D {
        public:
            Physics2D() = default;
            ~Physics2D() = default;

            static bool CheckCollision(const Rectangle& rec1, const Rectangle& rec2);
            static bool CheckCollision(RayLib::Vector2<float> point, const Rectangle& rec);

            static bool CheckCollision(const Circle& circle1, const Circle& circle2);
            static bool CheckCollision(const Rectangle& rec, const Circle& circle);

            static float RandomFloat(float a, float b);


        protected:
        private:
    };
}

#endif /* !PHYSICS2D_HPP_ */
