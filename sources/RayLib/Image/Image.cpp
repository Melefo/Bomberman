/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Image
*/

#include "Image.hpp"

namespace RayLib
{

    Image::Image(const std::string &fileName)
    {
        image = LoadImage(fileName.c_str());
    }

    Image::Image(const Image& newImage)
    {
        image = ImageCopy(newImage.image);
    }

    Image::Image(Vector2 size, Color color)
    {
        image = GenImageColor(static_cast<int>(size.x), static_cast<int>(size.y), {color.r, color.g, color.b, color.a});
    }

    Image::Image(const std::string &fileName, int *frames)
    {
        image = LoadImageAnim(fileName.c_str(), frames);
    }

    Image::~Image()
    {
        UnloadImage(image);
    }
}