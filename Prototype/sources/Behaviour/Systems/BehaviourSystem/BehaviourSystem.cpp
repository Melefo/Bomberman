/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** BehaviourSystem
*/

#include "BehaviourSystem.hpp"
#include "IBehaviour.hpp"
#include <iostream>

namespace Prototype
{
    BehaviourSystem::BehaviourSystem()
    {
        AddDependency<IBehaviour>();
    }

    void BehaviourSystem::Update(double dt, ECS::Entity& entity)
    {
        std::vector<std::reference_wrapper<IBehaviour>> behaviours = entity.OfType<IBehaviour>();

        std::cout << "Behaviour system updating" << std::endl;

        for (IBehaviour& behaviour : behaviours) {
            std::cout << "Behaviour component updating" << std::endl;
            behaviour.Update(dt);
        }
    }

}

