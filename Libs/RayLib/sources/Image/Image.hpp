/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Image
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <string>
#include <raylib.h>
#include "Color.hpp"
#include "Vector2.hpp"

namespace RayLib
{
    /**
     * @brief Image encapsulation
     * 
     */
    class Image {
        public:
            /**
             * @brief Destroy the Image object
             * 
             */
            ~Image();

            /**
             * @brief Construct a new Image object
             * 
             * @param image 
             */
            Image(const Image &image);

            /**
             * @brief Construct a new Image object
             * 
             * @param fileName 
             */
            Image(const std::string &fileName);

            /**
             * @brief Construct a new Image object
             * 
             * @param size 
             * @param color 
             */
            Image(Vector2<int> size, Color color=WHITE);

            /**
             * @brief Construct a new Image object
             * 
             * @param fileName 
             * @param frames 
             */
            Image(const std::string &fileName, int *frames);

            ::Image GetImage() const;

        protected:
        private:
            ::Image _image;
    };
}

#endif /* !IMAGE_HPP_ */
