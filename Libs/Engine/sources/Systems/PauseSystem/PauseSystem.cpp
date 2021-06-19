/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PauseSystem
*/

#include "PauseSystem.hpp"

namespace Component
{
    PauseSystem::PauseSystem() : _input(), _pauseSystem(false)
    {
        this->AddDependency<Button>();
    }

    void PauseSystem::Update(double, ECS::Entity& entity)
    {
        bool mmPauseButton = false;
        bool rPauseButton = false;
        if (entity.GetTag() == "MainMenuPauseButton")
            mmPauseButton = true;
        if (entity.GetTag() == "ReplayPauseButton")
            rPauseButton = true;
        if (!entity.HasComponent<Transform>())
            return;
        Transform& transform = entity.GetComponent<Transform>();
        std::unique_ptr<RayLib::Window>& windowRef = RayLib::Window::GetInstance(0, "");

        if (this->_input.IsKeyReleased(KeyboardKey::KEY_P) == true && _pauseSystem == false) {
            _pauseSystem = true;
            if (!ECS::Coordinator::GetInstance()->HasSystem<PhysicsSystem>() && !ECS::Coordinator::GetInstance()->HasSystem<BehaviourSystem>())
                return;
            ECS::Coordinator::GetInstance()->GetSystem<PhysicsSystem>().ToggleStatus();
            ECS::Coordinator::GetInstance()->GetSystem<BehaviourSystem>().ToggleStatus();
            if (mmPauseButton) {
                std::cout << "DETECT1";
                transform.position = RayLib::Vector3(windowRef->GetSize().x / 2.0f - 200.0f, windowRef->GetSize().y / 2.0f + 300.0f, 0.0f);
            }
            if (rPauseButton) {
                std::cout << "DETECT2";
                transform.position = RayLib::Vector3(windowRef->GetSize().x / 2.0f - 150.0f, windowRef->GetSize().y / 2.0f + 150.0f, 0.0f);
            }
        } else if (this->_input.IsKeyReleased(KeyboardKey::KEY_O) == true && _pauseSystem == true) {
            _pauseSystem = false;
            if (!ECS::Coordinator::GetInstance()->HasSystem<PhysicsSystem>() && !ECS::Coordinator::GetInstance()->HasSystem<BehaviourSystem>())
                return;
            ECS::Coordinator::GetInstance()->GetSystem<PhysicsSystem>().ToggleStatus();
            ECS::Coordinator::GetInstance()->GetSystem<BehaviourSystem>().ToggleStatus();
            if (mmPauseButton || rPauseButton)
                transform.position = RayLib::Vector3(10000.0f, 10000.0f, 10000.0f);
        }
    }

    void PauseSystem::FixedUpdate(ECS::Entity&)
    {
        /*std::vector<std::reference_wrapper<IBehaviour>> behaviours = entity.OfType<IBehaviour>();

        for (IBehaviour& behaviour : behaviours) {
            behaviour.FixedUpdate(entity);
        }*/
    }

    void PauseSystem::LateUpdate(double, ECS::Entity&)
    {
        /*std::vector<std::reference_wrapper<IBehaviour>> behaviours = entity.OfType<IBehaviour>();

        for (IBehaviour& behaviour : behaviours) {
            behaviour.LateUpdate(dt, entity);
        }*/
    }
}