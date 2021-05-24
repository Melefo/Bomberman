/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** SystemManager
*/

#include <algorithm>
#include "Exceptions.hpp"
#include "SystemManager.hpp"

namespace ECS
{
    template<typename T>
    void SystemManager::AddSystem()
    {
        std::string name(typeid(T).name());

        if (this->HasSystem<T>())
            throw new Exception::SystemManagerException("Cannot add more than once a system.");

        this->_systems.insert(name, std::make_unique<T>());
    }

    template<typename T>
    void SystemManager::RemoveSystem()
    {
        std::string name(typeid(T).name());

        auto &it = this->_systems.find(name);
        if (it != this->_systems.end())
            this->_systems.erase(it);
    }

    template<typename T>
    bool SystemManager::HasSystem()
    {
        std::string name(typeid(T).name());

        auto &it = this->_systems.find(name);
        return it != this->_systems.end();
    }

    const std::unordered_map<std::string, std::unique_ptr<ISystem>> &SystemManager::GetSystems() const
    {
        return this->_systems;
    }
}