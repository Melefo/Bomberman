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
    /**
     * @brief Rectangle encapsulation
     * 
     */
    class Rectangle {
        public:
            /**
             * @brief Construct a new Rectangle
             * 
             * @param newX 
             * @param newY 
             * @param newWidth 
             * @param newHeight 
             */
            Rectangle(float newX=0.0f,
                      float newY=0.0f,
                      float newWidth=1.0f,
                      float newHeight=1.0f);

            /**
             * @brief Construct a new Rectangle
             * 
             * @param other 
             */
            Rectangle(const Rectangle& other);

            /**
             * @brief Construct a new Rectangle object
             * 
             * @param other 
             */
            Rectangle(const ::Rectangle& other);

            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return Rectangle& 
             */
            Rectangle& operator=(const Rectangle& other);

            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return Rectangle& 
             */
            Rectangle& operator=(const ::Rectangle& other);

            /**
             * @brief Get the Rectangle as raylib structure
             * 
             * @return ::Rectangle 
             */
            ::Rectangle GetRectangle();

            /**
             * @brief Destroy the Rectangle object
             * 
             */
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
