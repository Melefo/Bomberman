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
#include "EngineExceptions.hpp"

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
            Drawable3D(const std::string& meshPath);

            /**
             * @brief Construct a new Drawable 3 D object
             * 
             * @param meshPath 
             * @param texturePath 
             */
            Drawable3D(const std::string& meshPath, const std::string& texturePath);

            /**
             * @brief Construct a new Drawable 3 D object
             * 
             * @param meshPath 
             * @param texturePath 
             * @param shaderPath 
             */
            Drawable3D(const std::string& meshPath, const std::string& texturePath, const std::string& shaderPath);
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

            void SetTexture(const std::string& path);
            void SetModel(const std::string& path);
            void SetShader(const std::string& path);

            RayLib::Model& GetModel(void);
            RayLib::Shader& GetShader(void);
            RayLib::Texture& GetTexture(void);

            // set rotation
            void RotateModel(RayLib::Vector3 rotation);

            void SetColor(RayLib::Color color);
            RayLib::Color& GetColor(void);

            std::ostream &operator<<(std::ostream &os) override;
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override;

        protected:
        private:
            std::shared_ptr<RayLib::Model> _model;
            std::shared_ptr<RayLib::Texture> _texture;
            std::shared_ptr<RayLib::Shader> _shader;
            RayLib::Color _color;

    };
}

#endif /* !Drawable3D_HPP_ */
