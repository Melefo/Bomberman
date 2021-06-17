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
    /**
     * @brief RenderTexture encapsulation
     * Generates a framebuffer for shader use
     */
    class RenderTexture {
        public:
            /**
             * @brief Construct a new Render Texture object
             * 
             * @param width Buffer screen width
             * @param height Buffer screen height
             */
            RenderTexture(int width, int height);
            /**
             * @brief Destroy the Render Texture object
             * 
             */
            ~RenderTexture();
            /**
             * @brief Unload the loaded framebuffer
             * 
             */
            void Unload();
            /**
             * @brief Initialize framebuffer for drawing
             * 
             */
            void BeginMode();
            /**
             * @brief End framebuffer drawing
             * 
             */
            void EndMode();
            /**
             * @brief Draw loaded framebuffer
             * 
             */
            void DrawTexture();
            /**
             * @brief Get the Texture object (framebuffer)
             * 
             * @return ::RenderTexture2D& 
             */
            ::RenderTexture2D& GetTexture();

        protected:
        private:
            /**
             * @brief RenderTexture framebuffer
             * 
             */
            ::RenderTexture2D _texture;
    };
};

#endif /* !RENDERTEXTURE_HPP_ */
