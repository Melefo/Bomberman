/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "IComponent.hpp"
#include "Model.hpp"
#include "Texture.hpp"

class Renderer : public ECS::IComponent {
    public:
        // ! insert default cube path here
        Renderer(const std::string& modelPath="../assets/models/cube/def_cube.obj",
                 const std::string& texturePath="../assets/models/cube/def_text.png");
        ~Renderer() override = default;

        RayLib::Model& GetModel(void);

    protected:
    private:
        RayLib::Model _model;
        RayLib::Texture _texture;
};

#endif /* !RENDERER_HPP_ */
