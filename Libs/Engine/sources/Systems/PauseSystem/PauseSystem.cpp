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
    }

    void PauseSystem::Update(double, ECS::Entity& entity)
    {
        if (this->_input.IsKeyReleased(KeyboardKey::KEY_P) == true) {
            if (!ECS::Coordinator::GetInstance()->HasSystem<PhysicsSystem>() && !ECS::Coordinator::GetInstance()->HasSystem<BehaviourSystem>())
                return;
            ECS::Coordinator::GetInstance()->GetSystem<PhysicsSystem>().ToggleStatus();
            ECS::Coordinator::GetInstance()->GetSystem<BehaviourSystem>().ToggleStatus();
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