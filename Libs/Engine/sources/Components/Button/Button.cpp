/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Button
*/

#include "Button.hpp"
#include <memory>
#include "Window.hpp"
#include "AssetCache.hpp"
#include "Physics2D.hpp"

namespace Component
{
    Button::Button(const std::string& path, bool lerp)
    : IUIObject(), _rect(0.0f, 0.0f, 0.0f, 0.0f), _tint(), _texture(AssetCache::GetAsset<RayLib::Texture>(path)), _lerp(lerp)
    {

    }

    void Button::Draw(RayLib::Vector2<float> position, RayLib::Vector2<float> scale)
    {
        RayLib::Vector3 vec3Pos = RayLib::Vector3(position.x, position.y, 0.0f);

        _rect.x = position.x;
        _rect.y = position.y;
        _rect.width = static_cast<float>(_texture->GetTexture().width) * scale.x;
        _rect.height = static_cast<float>(_texture->GetTexture().height) * scale.y;

        // ? multiplier scale par _rect scale ?

        if (this->_lerp && IsMouseOver()) {
            if (RayLib::Mouse::IsButtonDown(MOUSE_BUTTON_LEFT))
                _tint.Lerp(DARKGRAY, 0.25f);
            else
                _tint.Lerp(GRAY, 0.25f);
        } else {
            _tint.Lerp(WHITE, 0.25f);
        }

        _texture->DrawTextureNPatch(position, 0.0f, scale, _tint);
    }

    bool Button::IsMouseOver(void)
    {
        RayLib::Vector2<float> mousePos = RayLib::Mouse::GetPosition();
        std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(0, "");
        RayLib::Vector2<float> winSize = RayLib::Vector2<float>(static_cast<float>(window->GetSize().x),
                                                                static_cast<float>(window->GetSize().y));

        return (RayLib::Physics2D::CheckCollision(mousePos, _rect));
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

    ::Texture2D Button::GetTexture() const
    {
        return this->_texture->GetTexture();
    }
}

