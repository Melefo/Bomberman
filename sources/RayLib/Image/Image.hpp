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
    class Image {
        public:
            ~Image();

            Image(const Image &image);
            Image(const std::string &fileName);
            Image(Vector2 size, Color color=Color(255, 255, 255, 255));
            Image(const std::string &fileName, int *frames);

            ::Image image;

        protected:
        private:
    };
}

#endif /* !IMAGE_HPP_ */
