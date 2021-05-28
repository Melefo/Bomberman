/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Rectangle
*/

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include <raylib.h>

namespace RayLib
{
    class Rectangle {
        public:
            Rectangle(float newX=0.0f,
                      float newY=0.0f,
                      float newWidth=1.0f,
                      float newHeight=1.0f);

            Rectangle(const Rectangle& other);
            Rectangle(const ::Rectangle& other);

            Rectangle& operator=(const Rectangle& other);
            Rectangle& operator=(const ::Rectangle& other);

            ::Rectangle GetRectangle();

            ~Rectangle() = default;

            float x;
            float y;
            float width;
            float height;
        protected:
        private:
    };
}

#endif /* !RECTANGLE_HPP_ */
