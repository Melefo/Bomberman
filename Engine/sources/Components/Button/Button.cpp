/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Button
*/

#include "Button.hpp"
#include <memory>
#include "Window.hpp"
#include "Physics3D.hpp"

namespace Component
{
    Button::Button()
    : IUIObject(), _rect(0.0f, 0.0f, 0.0f, 0.0f)
    {
    }

    void Button::Draw(RayLib::Vector2<float> position, Asset& asset, RayLib::Vector2<float> scale)
    {
        RayLib::Vector3 vec3Pos = RayLib::Vector3(position.x, position.y, 0.0f);
        RayLib::Texture& texture = asset.getTexture();

        _rect.x = position.x;
        _rect.y = position.y;
        _rect.width = static_cast<float>(texture.GetTexture().width);
        _rect.height = static_cast<float>(texture.GetTexture().height);

        //_texture.DrawTexture( position, GREEN);

        // ? multiplier scale par _rect scale ?

        // todo if is mouse over, change color (grey, dark grey)
        texture.DrawTextureEx(position, 0.0f, scale.x, WHITE);
    }

    bool Button::IsMouseOver(void)
    {
        RayLib::Vector2<float> mousePos = RayLib::Mouse::GetPosition();
        std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(0, "");
        RayLib::Vector2<float> winSize = RayLib::Vector2<float>(static_cast<float>(window->GetSize().x),
                                                                static_cast<float>(window->GetSize().y));

        return (RayLib::Physics3D::CheckCollision(mousePos, _rect));
        //return (RayLib::Physics3D::CheckCollision(mouseRay, _bounds).HasHit());
    }

    void Button::AddCallback(std::function<void()> callBack)
    {
        _callbacks.push_back(callBack);
    }

    void Button::OnClick(void)
    {
        for (auto callback : _callbacks) {
            callback();
        }
    }
}

