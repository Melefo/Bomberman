/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** BehaviourSystem
*/

#include "BehaviourSystem.hpp"
#include "IBehaviour.hpp"
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
            behaviour.Update(dt);
        }
    }

}

