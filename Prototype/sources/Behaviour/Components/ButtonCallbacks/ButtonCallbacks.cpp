/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** ButtonCallbacks
*/

#include "ButtonCallbacks.hpp"

namespace Prototype
{
    ButtonCallbacks::ButtonCallbacks(ECS::Entity& attatchedEntity) :
    _entity(attatchedEntity), _button(_entity.GetComponent<Button>())
    {
        // add our callback
        _button.AddCallback(std::bind(&ButtonCallbacks::SayHello, this));
    }

    void ButtonCallbacks::Update(float dt)
    {
        (void) dt;
        if (_button.IsMouseOver() && RayLib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT)) {
            _button.OnClick();
        }
    }

    void ButtonCallbacks::FixedUpdate(ECS::Entity& entity)
    {
        (void) entity;
    }


    void ButtonCallbacks::SayHello()
    {
        std::cout << "Hello!" << std::endl;
    }
}