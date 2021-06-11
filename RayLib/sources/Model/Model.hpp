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
    /**
     * @brief Model encapsulation
     * 
     */
    class Model {
        public:
            /**
             * @brief Construct a new Model object based on given file
             * 
             * @param fileName 
             */
            Model(const std::string& fileName);

            /**
             * @brief Construct a new Model object based on mesh
             * 
             * @param mesh 
             */
            Model(Mesh mesh);

            /**
             * @brief Destroy the Model object
             * 
             */
            ~Model();

            /**
             * @brief Draw model at position, with scale, and tint
             * 
             * @param position 
             * @param scale 
             * @param tint 
             */
            void Draw(Vector3 position, float scale, Color tint);

            /**
             * @brief Draw model, with rotation parameters
             * 
             * @param position 
             * @param rotationAxis 
             * @param rotationAngle 
             * @param scale 
             * @param tint 
             */
            void DrawEx(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);

            /**
             * @brief Set the Material's Texture
             * 
             * @param matIndex default 0
             * @param mapType default MATERIAL_MAP_DIFFUSE
             * @param text 
             */
            void SetMaterialTexture(int matIndex, int mapType, Texture& text);

            void SetMaterialShader(int matIndex, Shader& shader);

            /**
             * @brief Get the Model object as a raylib structure
             * 
             * @return ::Model 
             */
            const ::Model GetModel();

        protected:
        private:
            ::Model _model;
    };
}

#endif /* !MODEL_HPP_ */
