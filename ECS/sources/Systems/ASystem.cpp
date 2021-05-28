/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** ASystem
*/

#include "ASystem.hpp"

namespace ECS
{
    const std::vector<std::string> &ASystem::GetDependencies() const
    {
        return this->_dependencies;
    }

    void ASystem::Update(double, Entity &)
    {

    }
}