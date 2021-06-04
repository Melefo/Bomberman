/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** ComponentManager
*/

#include "ComponentManager.hpp"

namespace ECS
{
    ComponentManager::ComponentManager() :
    _bases(), _components()
    {
    }

    bool ComponentManager::HasComponent(std::string& name) const
    {
        if (this->_bases.find(name) != this->_bases.end())
            return (true);
        return this->_components.find(name) != this->_components.end();
    }

    bool ComponentManager::HasComponents(std::vector<std::string>& names) const
    {
        for (auto& name : names)
            if (!this->HasComponent(name))
                return false;
        return true;
    }
}