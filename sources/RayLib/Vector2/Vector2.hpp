/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Vector2
*/

#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

#include <raylib.h>


namespace RayLib
{
    template <typename T>
    class Vector2
    {
        public:

            Vector2<T>(void)
            {
                x = 0;
                y = 0;
            }

            ~Vector2<T>(void) = default;

            Vector2<T>(T newX)
            {
                x = newX;
            }

            Vector2<T>(T newX, T newY)
            {
                x = newX;
                y = newY;
            }

            Vector2<T>(const Vector2<T> &vec)
            {
                x = vec.x;
                y = vec.y;
            }

            Vector2<T>(const ::Vector2 &vec)
            {
                x = static_cast<T>(vec.x);
                y = static_cast<T>(vec.y);
            }

            ::Vector2 getVector2(void)
            {
                ::Vector2 vec = {x, y};

                return (vec);
            }

            Vector2<T>& operator=(const Vector2<T> &vec)
            {
                x = vec.x;
                y = vec.y;
                return (*this);
            }

            //Vector2 &operator+(const Vector2 &Vector2);
            //Vector2 &operator-(const Vector2 &Vector2);
            // dot product ?


            T x;
            T y;
        protected:
        private:
    };
}
#endif /* !VECTOR2_HPP_ */
