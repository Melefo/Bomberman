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
#include "IAsset.hpp"
#include "Shader.hpp"

namespace RayLib
{
    /**
     * @brief Texture encapsulation
     * 
     */
    class Texture : public IAsset {
        public:
            /**
             * @brief Destroy the Texture object
             *
             */
            ~Texture() override;

            /**
             * @brief Construct a new Texture object from a file
             *
             * @param filename
             */
            Texture(const std::string& filename="../assets/Default_texture.png");

            /**
             * @brief Construct a new Texture from an existing image
             *
             * @param image
             * @param isCubemap Is the image a cubemap
             */
            Texture(Image image, bool isCubemap = false);

            /**
             * @brief Construct a new Texture object used in cubemap backgrounds
             * 
             * @param shader
             * @param texture
             * @param size 
             * @param format 
             */
            Texture(RayLib::Shader& shader, RayLib::Texture& texture, int size, float format);

            /**
             * @brief Construct a new Texture object
             * 
             * @param texture 
             */
            Texture(::Texture texture);

            /**
             * @brief Draw texture on screen
             *
             * @param position
             * @param tint
             */
            void DrawTexture(Vector2<float> position, Color tint);

            /**
             * @brief Draw texture on screen
             *
             * @param position
             * @param rotation
             * @param scale
             * @param tint
             */
            void DrawTextureEx(Vector2<float> position, float rotation, float scale, Color tint);

            /**
             * @brief Draw texture on screen using rectangle's dimensions
             * 
             * @param source 
             * @param position 
             * @param col 
             */
            void DrawTextureRec(RayLib::Rectangle source, RayLib::Vector2<float> position=RayLib::Vector2<float>(), RayLib::Color col=WHITE);

            /**
             * @brief Draw billboard
             * cf: https://www.raylib.com/examples/web/models/loader.html?name=models_billboard
             * @param camera
             * @param center
             * @param size
             * @param tint
             */
            void DrawBillboard(RayLib::Camera3D camera, RayLib::Vector3 center=RayLib::Vector3(), float size=1.0f, Color tint=WHITE);

            void DrawTextureNPatch(Vector2<float> position, float rotation, Vector2<float> scale, Color tint);
            /**
             * @brief Get the Texture as a raylib structure
             * 
             * @return ::Texture2D 
             */
            ::Texture2D GetTexture();

            const std::string& GetFileName() const;

        protected:
        private:
            ::Texture2D _texture;
            std::string _fileName;
    };
}

#endif /* !TEXTURE_HPP_ */
