/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Explosion
*/

#include "Explosion.hpp"
#include <iostream>

namespace Prototype
{
    Explosion::Explosion(RayLib::Vector3 startRadius, Explosion::ExplosionType startType, unsigned int startPower, float timer) :
    _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype"))
    {
        radius = startRadius;
        type = startType;
        power = startPower;
        _explosionTimer = timer;
    }

    void Explosion::Update(float dt)
    {
        (void) dt;
        _explosionTimer -= _window->GetFrameTime();

        if (_explosionTimer <= 0.0f) {
            std::cout << "BOOM" << std::endl;
            // destroy self
            // .dispose
        }
    }

    void Explosion::FixedUpdate(ECS::Entity& entity)
    {
        (void) entity;
    }
}