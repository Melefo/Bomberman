/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** BehaviourSystem
*/

#include "BehaviourSystem.hpp"
#include "Behaviour.hpp"
#include <iostream>

namespace Prototype
{
    BehaviourSystem::BehaviourSystem()
    {
        AddDependency<Behaviour>();
    }

    void BehaviourSystem::Update(double dt, ECS::Entity& entity)
    {
        Behaviour& behaviour = entity.GetComponent<Behaviour>();

        std::cout << "Behaviour system updating" << std::endl;
        behaviour.Update(dt);
    }

}

