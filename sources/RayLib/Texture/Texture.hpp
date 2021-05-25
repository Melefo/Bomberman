/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <raylib.h>
#include <string>
#include "Image.hpp"
#include "Color.hpp"
#include "Vector2.hpp"

namespace RayLib
{
    class Texture {
        public:
            ~Texture();

            Texture(const std::string& filename);
            Texture(const Image& image);

            void DrawTexture(Vector2<float> position, Color tint);
            void DrawTextureEx(Vector2<float> position, float rotation, float scale, Color tint);

            ::Texture2D GetTexture();

        protected:
        private:
            ::Texture2D _texture;
    };
}

#endif /* !TEXTURE_HPP_ */
