/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Vector2
*/

#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

#include <raylib/include/raylib.h>

namespace RayLib
{
    class Vector2
    {
        public:
            Vector2();
            Vector2(float x);
            Vector2(float x, float y);
            Vector2(float x, float y, float z);
            Vector2(const ::Vector2 &vec);

            ~Vector2();

            Vector2 &operator=(const ::Vector2 &Vector2);

            ::Vector2 vector2;
        protected:
        private:
    };
}
#endif /* !VECTOR2_HPP_ */
