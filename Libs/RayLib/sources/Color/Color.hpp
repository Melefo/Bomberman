/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <raylib.h>
#include "Vector3.hpp"

namespace RayLib
{
    /**
     * @brief RayLib Color encapsulation
     *
     */
    class Color : public ::Color {
        public:
            /**
             * @brief Construct a new Color object
             * Initialize all values to zero
             */
            Color();

            /**
             * @brief Construct a new Color object
             *
             * @param vec based on the values in vector3, alpha is initialized to 0
             */
            Color(const Vector3 &vec);

            /**
             * @brief Copy constructor from other Color class
             * 
             * @param col 
             */
            Color(const Color &col);

            /**
             * @brief Construct a new Color object from a raylib color structure
             * 
             * @param col 
             */
            Color(const ::Color &col);

            /**
             * @brief Construct a new Color object based on given values
             * 
             * @param red 
             * @param green 
             * @param blue 
             * @param alpha 
             */
            Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

            /**
             * @brief Destroy the Color object
             * 
             */
            ~Color() = default;

            /**
             * @brief Get the color as a raylib Color structure
             * 
             * @return ::Color 
             */
            ::Color getColor(void);

            /**
             * @brief assignment operator
             * 
             * @param col 
             * @return Color& 
             */
            Color &operator=(const Color &col);

            /**
             * @brief Linearly interpolate vector3 to target by t
             * 
             * @param target 
             * @param t 
             */
            void Lerp(Color target, float t);

        protected:
        private:
    };
}

#endif /* !COLOR_HPP_ */
