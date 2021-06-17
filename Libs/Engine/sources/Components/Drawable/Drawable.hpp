/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <raylib.h>
#include "Model.hpp"
#include "IComponent.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

namespace Component
{
    class Drawable : public ECS::IComponent {
        public:
            Drawable(RayLib::Mesh& mesh);
            Drawable(const std::string& path);
            ~Drawable() = default;

            void Draw(RayLib::Vector3 position, RayLib::Vector3 rotationAxis, float rotationAngle, RayLib::Vector3 scale, RayLib::Color tint);
            void SetMaterialTexture(int matIndex, int mapType, RayLib::Texture& text);
            void SetMaterialShader(int matIndex, RayLib::Shader& shader);

            std::ostream &operator<<(std::ostream &os) override {return os;};
            std::istream &operator>>(std::istream &is) override {return is;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

        protected:
        private:
            RayLib::Model _model;
    };
}

#endif /* !DRAWABLE_HPP_ */
