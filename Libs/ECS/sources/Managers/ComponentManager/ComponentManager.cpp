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

    IComponent& ComponentManager::GetComponentByName(const std::string& name)
    {
        const auto &it = this->_components.find(name);

        if (it == this->_components.end())
            throw Exception::EntityException("Entity doesn't contain this Component");
        return (*it->second);
    }

    std::vector<std::reference_wrapper<std::unique_ptr<IComponent>>> ComponentManager::GetComponents()
    {
        std::vector<std::reference_wrapper<std::unique_ptr<IComponent>>> comps;

        for (auto it = _components.begin(); it != _components.end(); it++)
            comps.push_back(it->second);
        return (comps);
    }

}