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
    class Color {
        public:
            Color();
            Color(const Vector3 &vec);
            Color(const Color &col);
            Color(const ::Color &col);
            Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

            ~Color();

            ::Color getColor(void);

            Color &operator=(const Color &col);


            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;

        protected:
        private:
    };
}

#endif /* !COLOR_HPP_ */
