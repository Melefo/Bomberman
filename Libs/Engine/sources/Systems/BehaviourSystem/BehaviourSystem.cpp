/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** BehaviourSystem
*/

#include "BehaviourSystem.hpp"
#include "GameConfiguration.hpp"
#include <iostream>

namespace Component
{
    BehaviourSystem::BehaviourSystem()
    {
        AddDependency<IBehaviour>();
    }

    void BehaviourSystem::Update(double dt, ECS::Entity& entity)
    {
        std::vector<std::reference_wrapper<IBehaviour>> behaviours = entity.OfType<IBehaviour>();

        for (IBehaviour& behaviour : behaviours) {
            behaviour.Update(dt, entity);
        }
    }

    void BehaviourSystem::FixedUpdate(ECS::Entity &entity)
    {
        std::vector<std::reference_wrapper<IBehaviour>> behaviours = entity.OfType<IBehaviour>();

        for (IBehaviour& behaviour : behaviours) {
            behaviour.FixedUpdate(entity);
        }
    }

    void BehaviourSystem::LateUpdate(double dt, ECS::Entity& entity)
    {
        std::vector<std::reference_wrapper<IBehaviour>> behaviours = entity.OfType<IBehaviour>();

        for (IBehaviour& behaviour : behaviours) {
            behaviour.LateUpdate(dt, entity);
        }
    }

}

