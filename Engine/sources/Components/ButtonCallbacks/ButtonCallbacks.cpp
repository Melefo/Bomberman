/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** ButtonCallbacks
*/

#include "Window.hpp"
#include "ButtonCallbacks.hpp"

namespace Component
{
    ButtonCallbacks::ButtonCallbacks(ECS::Entity& attatchedEntity) :
    _entity(attatchedEntity), _button(_entity.GetComponent<Button>())
    {
        // add our callback
        //_button.AddCallback(std::bind(&ButtonCallbacks::QuitWindow, this));
    }

    void ButtonCallbacks::Update(double, ECS::Entity&)
    {
        if (_button.IsMouseOver() && RayLib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT)) {
            _button.OnClick();
        }
    }

    void ButtonCallbacks::FixedUpdate(ECS::Entity&)
    {
    }

    void ButtonCallbacks::LateUpdate(double, ECS::Entity&)
    {

    }

    void ButtonCallbacks::StaticCallback(void)
    {
        std::cout << "Hello from static callback!" << std::endl;
    }

    void ButtonCallbacks::SayHello()
    {
        std::cout << "Hello!" << std::endl;
    }

    void ButtonCallbacks::QuitWindow()
    {
        ECS::Coordinator::GetInstance()->CloseWindow = true;
        std::cout << "quited" << std::endl;
    }

    void ButtonCallbacks::CreateBox()
    {
        std::cout << "createBox" << std::endl;
    }

}