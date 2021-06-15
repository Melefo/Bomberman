/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RenderTexture
*/

#ifndef RENDERTEXTURE_HPP_
#define RENDERTEXTURE_HPP_

#include <raylib.h>

namespace RayLib {
    class RenderTexture {
        public:
            RenderTexture(int width, int height) : _texture(::LoadRenderTexture(width, height)) {};
            ~RenderTexture() {Unload();};

            void Unload() {::UnloadRenderTexture(_texture);};

            void BeginMode() {::BeginTextureMode(_texture);};

            void EndMode() {::EndTextureMode();};

            void DrawTexture() {
                ::DrawTextureRec(_texture.texture, {0, 0, static_cast<float>(_texture.texture.width), static_cast<float>(-_texture.texture.height)}, {0, 0}, ::WHITE);
            };

            ::RenderTexture2D& GetTexture() {return _texture;};

        protected:
        private:
            ::RenderTexture2D _texture;
    };
};

#endif /* !RENDERTEXTURE_HPP_ */
