/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Drawable3D
*/

#ifndef Drawable3D_HPP_
#define Drawable3D_HPP_

#include <raylib.h>
#include "Model.hpp"
#include "IComponent.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

namespace Component
{
    class Drawable3D : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Drawable 3D object from mesh
             * 
             * @param mesh 
             */
            Drawable3D(RayLib::Mesh& mesh);
            /**
             * @brief Construct a new Drawable 3 D object from path
             * 
             * @param path 
             */
            Drawable3D(const std::string& path);
            /**
             * @brief Destroy the Drawable 3 D object
             * 
             */
            ~Drawable3D() override = default;

            /**
             * @brief Draw model at position, axis, angle, scale
             * 
             * @param position 
             * @param rotationAxis 
             * @param rotationAngle 
             * @param scale 
             * @param tint 
             */
            void Draw(RayLib::Vector3 position, RayLib::Vector3 scale, RayLib::Color tint);
            void SetMaterialTexture(int matIndex, int mapType, RayLib::Texture& text);
            void SetMaterialShader(int matIndex, RayLib::Shader& shader);

            // set rotation
            void RotateModel(RayLib::Vector3 rotation);

            std::ostream &operator<<(std::ostream &os) override {return os;};
            std::istream &operator>>(std::istream &is) override {return is;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

        protected:
        private:
            RayLib::Model _model;
    };
}

#endif /* !Drawable3D_HPP_ */
