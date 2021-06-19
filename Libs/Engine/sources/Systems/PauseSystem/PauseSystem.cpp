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
        bool pauseText = false;
        if (entity.GetTag() == "MainMenuPauseButton")
            mmPauseButton = true;
        if (entity.GetTag() == "ReplayPauseButton")
            rPauseButton = true;
        if (entity.GetTag() == "PauseText")
            pauseText = true;
        if (!entity.HasComponent<Transform>())
            return;
        Transform& transform = entity.GetComponent<Transform>();
        std::unique_ptr<RayLib::Window>& windowRef = RayLib::Window::GetInstance(0, "");

        if (this->_input.IsKeyReleased(KeyboardKey::KEY_P) == true) {
            if (!ECS::Coordinator::GetInstance()->HasSystem<PhysicsSystem>() && !ECS::Coordinator::GetInstance()->HasSystem<BehaviourSystem>())
                return;
            if (mmPauseButton) {
                transform.position = RayLib::Vector3(windowRef->GetSize().x / 2.0f - 200.0f, windowRef->GetSize().y / 2.0f + 300.0f, -100.0f);
            }
            if (rPauseButton) {
                transform.position = RayLib::Vector3(windowRef->GetSize().x / 2.0f - 200.0f, windowRef->GetSize().y / 2.0f + 150.0f, -100.0f);
            }
            if (pauseText) {
                transform.position = RayLib::Vector3(windowRef->GetSize().x / 2.0f - 200.0f, windowRef->GetSize().y / 2.0f - 150.0f, -100.0f);
            }
            if (!_pauseSystem) {
                ECS::Coordinator::GetInstance()->GetSystem<PhysicsSystem>().ToggleStatus();
                ECS::Coordinator::GetInstance()->GetSystem<BehaviourSystem>().ToggleStatus();
            }
            _pauseSystem = true;
        } else if (this->_input.IsKeyReleased(KeyboardKey::KEY_O) == true) {
            if (!ECS::Coordinator::GetInstance()->HasSystem<PhysicsSystem>() && !ECS::Coordinator::GetInstance()->HasSystem<BehaviourSystem>())
                return;
            if (mmPauseButton || rPauseButton || pauseText)
                transform.position = RayLib::Vector3(10000.0f, 10000.0f, 10000.0f);
            if (_pauseSystem) {
                ECS::Coordinator::GetInstance()->GetSystem<PhysicsSystem>().ToggleStatus();
                ECS::Coordinator::GetInstance()->GetSystem<BehaviourSystem>().ToggleStatus();
            }
            _pauseSystem = false;
        }
    }

    void PauseSystem::FixedUpdate(ECS::Entity &entity)
    {
        /*std::vector<std::reference_wrapper<IBehaviour>> behaviours = entity.OfType<IBehaviour>();

        for (IBehaviour& behaviour : behaviours) {
            behaviour.FixedUpdate(entity);
        }*/
    }

    void PauseSystem::LateUpdate(double dt, ECS::Entity& entity)
    {
        /*std::vector<std::reference_wrapper<IBehaviour>> behaviours = entity.OfType<IBehaviour>();

        for (IBehaviour& behaviour : behaviours) {
            behaviour.LateUpdate(dt, entity);
        }*/
    }
}