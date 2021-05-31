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

namespace Prototype
{
    Button::Button(RayLib::Camera3D& camera, const std::string& texturePath)
    : IUIObject(), _camera(camera), _texture(texturePath), _rect(0.0f, 0.0f, _texture.GetTexture().width, _texture.GetTexture().height),
    _bounds(0.0f, 0.0f)
    {
    }

    void Button::Draw(RayLib::Vector2<float> position, float scale)
    {
        RayLib::Vector3 vec3Pos = RayLib::Vector3(position.x, position.y, 0.0f);

        _rect.width *= scale;
        _rect.height *= scale;
        _bounds.InitFromCube(RayLib::Vector3(position.x, position.y), RayLib::Vector3(scale, scale, 0.1f));

        //_texture.DrawTextureRec(_rect, position, WHITE);
        _texture.DrawBillboard(_camera, vec3Pos, scale, WHITE);
    }

    bool Button::IsMouseOver(void)
    {
        RayLib::Vector2<float> mousePos = RayLib::Mouse::GetPosition();
        std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(0.0f, "");
        RayLib::Vector2<float> winSize = RayLib::Vector2<float>(static_cast<float>(window->GetSize().x),
                                                                static_cast<float>(window->GetSize().y));

        RayLib::Ray mouseRay = _camera.GetMouseRay(mousePos);

        //CheckCollision(Ray ray, BoundingBox box);                                            // Detect collision between ray and box


        RayLib::Rectangle bounds = {winSize.x / 2.0f, winSize.y / 2.0f, _rect.width, _rect.height};

        //return (RayLib::Physics3D::CheckCollision(mousePos, bounds));
        return (RayLib::Physics3D::CheckCollision(mouseRay, _bounds).HasHit());
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

