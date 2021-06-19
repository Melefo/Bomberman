/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PauseSystem
*/

#include "PauseSystem.hpp"

namespace Component
{
    PauseSystem::PauseSystem() : _input()
    {
        this->AddDependency<Camera>();
    }

    void PauseSystem::Update(double, ECS::Entity&)
    {
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

        std::cout << this->_input.GetKeyPressed() << std::endl;
        if (this->_input.IsKeyPressed(KeyboardKey::KEY_ESCAPE) == true)
        {
            if (coordinator->getCurrentScene() == "Game")
                coordinator->setCurrentScene("Pause");
            else if (coordinator->getCurrentScene() == "Pause")
                coordinator->setCurrentScene("Game");
        }
    }

    void PauseSystem::FixedUpdate(ECS::Entity&)
    {
    }

    void PauseSystem::LateUpdate(double, ECS::Entity&)
    {
    }
}