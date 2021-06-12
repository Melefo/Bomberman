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
    /**
     * @brief Vector2 encapsulation
     * 
     * @tparam T typically <int> or <float>
     */
    template <typename T>
    class Vector2
    {
        public:

            /**
             * @brief Construct a new Vector 2<T> object
             * Initialise parameters to zero
             */
            Vector2<T>(void) :
            x(0), y(0)
            {
            }

            /**
             * @brief Destroy the Vector 2<T> object
             * 
             */
            ~Vector2<T>() = default;

            /**
             * @brief Construct a new Vector 2<T> object
             * 
             * @param newX set x parameter
             */
            Vector2<T>(T newX) :
            x(newX), y(0)
            {
            }

            /**
             * @brief Construct a new Vector 2<T>
             *
             * @param newX set x parameter
             * @param newY set y parameter
             */
            Vector2<T>(T newX, T newY) :
            x(newX), y(newY)
            {
            }

            /**
             * @brief Construct a new Vector 2<T>
             *
             * @param vec 
             */
            Vector2<T>(const Vector2<T>& vec) :
            x(vec.x), y(vec.y)
            {

            }

            /**
             * @brief Construct a new Vector 2<T> object
             * 
             * @param vec 
             */
            Vector2<T>(const ::Vector2& vec) :
            x(static_cast<T>(vec.x)), y(static_cast<T>(vec.y))
            {
            }

            /**
             * @brief Get the Vector2 raylib structure
             *
             * @return ::Vector2
             */
            ::Vector2 getVector2(void)
            {
                ::Vector2 vec = {x, y};

                return (vec);
            }

            /**
             * @brief Assignment operator
             *
             * @param vec
             * @return Vector2<T>&
             */
            Vector2<T>& operator=(const Vector2<T>& vec)
            {
                x = vec.x;
                y = vec.y;
                return (*this);
            }

            //Vector2 &operator+(const Vector2 &Vector2);
            //Vector2 &operator-(const Vector2 &Vector2);
            // dot product ?

            /**
             * @brief Multiply vector by factor
             *
             * @param factor
             * @return Vector2<T>&
             */
            Vector2<T>& operator*(const float& factor)
            {
                x *= factor;
                y *= factor;
                return (*this);
            }

            T x;
            T y;
        protected:
        private:
    };
}
#endif /* !VECTOR2_HPP_ */
