/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Vector2
*/

#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

#include <raylib.h>
#include <cmath>
#include "Vector3.hpp"
#include "IXMLSerializable.hpp"

namespace RayLib
{
    /**
     * @brief Vector2 encapsulation
     * 
     * @tparam T typically <int> or <float>
     */
    template <typename T>
    class Vector2 : public IXMLSerializable
    {
        public:
            using value_type = T;

            /**
             * @brief Construct a new Vector 2<T> object
             * Initialise parameters to zero
             */
            Vector2(void) :
            x(0), y(0)
            {
            }

            /**
             * @brief Destroy the Vector 2<T> object
             * 
             */
            ~Vector2() = default;

            /**
             * @brief Construct a new Vector 2<T> object
             * 
             * @param newX set x parameter
             */
            Vector2(T newX) :
            x(newX), y(0)
            {
            }

            /**
             * @brief Construct a new Vector 2<T>
             *
             * @param newX set x parameter
             * @param newY set y parameter
             */
            Vector2(T newX, T newY) :
            x(newX), y(newY)
            {
            }

            /**
             * @brief Construct a new Vector 2<T>
             *
             * @param vec 
             */
            Vector2(const Vector2<T>& vec) :
            x(vec.x), y(vec.y)
            {

            }

            /**
             * @brief Construct a new Vector 2<T>
             *
             * @param vec 
             */
            Vector2(const Vector3& vec) :
            x(static_cast<T>(vec.x)), y(static_cast<T>(vec.z))
            {

            }

            /**
             * @brief Construct a new Vector 2<T> object
             * 
             * @param vec 
             */
            Vector2(const ::Vector2& vec) :
            x(static_cast<T>(vec.x)), y(static_cast<T>(vec.y))
            {
            }


            /**
             * @brief Get the Vector2 raylib structure
             *
             * @return ::Vector2
             */
            ::Vector2 getVector2(void) const
            {
                ::Vector2 vec = {static_cast<float>(x), static_cast<float>(y)};

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

            Vector2<T>& operator+=(const Vector2<T>& other)
            {
                x += other.x;
                y += other.y;
                return (*this);
            }

            Vector2<T>& operator-=(const Vector2<T>& other)
            {
                x -= other.x;
                y -= other.y;
                return (*this);
            }

            Vector2<T> operator-(const Vector2<T>& other)
            {
                return (Vector2<T>(x - other.x, y - other.y));
            }

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
                x = static_cast<T>(x * factor);
                y = static_cast<T>(y * factor);
                return (*this);
            }

            float Distance(const Vector2<T>& other)
            {
                float distance = static_cast<float>(std::sqrt(std::pow(static_cast<double>(x - other.x), 2.0) +
                                                         std::pow(static_cast<double>(y - other.y), 2.0)));

                return (distance);
            }

            std::ostream& operator<<(std::ostream& os) override
            {
                os << "<Vector2>";
                os << "<x>" << x << "</x>";
                os << "<y>" << y << "</y>";
                os << "</Vector2>";
                return (os);
            }

            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override
            {
                boost::property_tree::ptree vec2 = ptree.get_child("Vector2");

                x = vec2.get<T>("x");
                y = vec2.get<T>("y");
                return (ptree);
            }

            T x;
            T y;
        protected:
        private:
    };
}

#endif /* !VECTOR2_HPP_ */
