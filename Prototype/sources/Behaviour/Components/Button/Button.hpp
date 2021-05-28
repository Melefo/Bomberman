/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "IComponent.hpp"
#include <functional>
#include <vector>
#include "Texture.hpp"
#include "IUIObject.hpp"

namespace Prototype
{
    class Button : public IUIObject {
        public:
            Button(RayLib::Camera3D& camera, const std::string& texturePath="../assets/models/cube/def_text.png");
            ~Button() override = default;

            void Draw(RayLib::Vector2<float> position, float scale=1.0f) override;
            // todo isMouseOver
            // todo addCallback
            // todo onClick (call callbacks)
        protected:
        private:
            //! ou billboard
            RayLib::Camera3D& _camera;
            RayLib::Texture _texture;
            std::vector<std::function<void()>> _callbacks;
    };
}

#endif /* !BUTTON_HPP_ */
