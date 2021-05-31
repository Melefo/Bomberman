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
#include "Camera3D.hpp"
#include "Rectangle.hpp"

namespace RayLib
{
    class Texture {
        public:
            ~Texture();

            Texture(const std::string& filename);
            Texture(Image image);

            void DrawTexture(Vector2<float> position, Color tint);
            void DrawTextureEx(Vector2<float> position, float rotation, float scale, Color tint);
            void DrawTextureRec(RayLib::Rectangle source, RayLib::Vector2<float> position=RayLib::Vector2<float>(), RayLib::Color col=WHITE);

            // draw billboard ?
            void DrawBillboard(RayLib::Camera3D camera, RayLib::Vector3 center=RayLib::Vector3(), float size=1.0f, Color tint=WHITE);



            ::Texture2D GetTexture();

        protected:
        private:
            ::Texture2D _texture;
    };
}

#endif /* !TEXTURE_HPP_ */
