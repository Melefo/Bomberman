/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Model
*/

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <raylib.h>
#include <string>
#include "Vector3.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"

namespace RayLib
{
    class Model {
        public:
            Model(const std::string& fileName);
            Model(Mesh mesh);
            ~Model();

            void Draw(Vector3 position, float scale, Color tint);
            void DrawEx(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);

            void SetMaterialTexture(int matIndex, int mapType, Texture& text);

        protected:
        private:
            ::Model _model;
    };
}

#endif /* !MODEL_HPP_ */
