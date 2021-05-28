/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** ASystem
*/

#include "ASystem.hpp"

namespace ECS
{
    ASystem::ASystem() :
    _dependencies(), _enabled(true)
    {
    }

    ASystem::ASystem(bool enabled) :
    _dependencies(), _enabled(enabled)
    {
    }

    const std::vector<std::string> &ASystem::GetDependencies() const
    {
        return this->_dependencies;
    }

    void ASystem::Update(double, Entity &)
    {
    }

    void ASystem::OnDisable()
    {
    }

    void ASystem::OnEnable()
    {
    }

    bool ASystem::GetStatus() const
    {
        return this->_enabled;
    }

    void ASystem::ToggleStatus()
    {
        this->_enabled = !this->_enabled;
    
        if (this->_enabled)
            this->OnEnable();
        else
            this->OnDisable();
    }
}