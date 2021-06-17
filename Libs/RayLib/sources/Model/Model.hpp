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
#include "Shader.hpp"
#include <raymath.h>

namespace RayLib
{
    /**
     * @brief Model encapsulation
     * 
     */
    class Model : public IXMLSerializable {
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
            Model(Mesh& mesh);

            /**
             * @brief Construct a new Model object
             * Create a cube mesh and create from there
             */
            Model();

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

            /**
             * @brief Set the Material's Shader
             * 
             * @param matIndex default 0
             * @param shader The Shader to assign
             */
            void SetMaterialShader(int matIndex, Shader& shader);

            /**
             * @brief Get the Model object as a raylib structure
             * 
             * @return ::Model 
             */
            const ::Model GetModel();

            const std::string& GetFileName() const;

            void RotateModel(RayLib::Vector3 rotation);

            std::ostream& operator<<(std::ostream& os) override;
            std::istream& operator>>(std::istream& is) override;

            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override;

        protected:
        private:
            /**
             * @brief The C raylib's Model structure
             * 
             */
            ::Model _model;
            std::string _fileName;
    };
}

#endif /* !MODEL_HPP_ */
