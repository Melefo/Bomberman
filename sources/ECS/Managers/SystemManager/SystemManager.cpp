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

        this->_systems.emplace_back(std::make_unique<T>());
    }

    template<typename T>
    void SystemManager::RemoveSystem()
    {
        std::string name(typeid(T).name());

        for (auto it = this->_systems.begin(); it != this->_systems.end(); it++)
            if ((*it)->GetName() == name)
            {
                this->_systems.erase(it);
                return;
            }
    }

    template<typename T>
    bool SystemManager::HasSystem()
    {
        std::string name(typeid(T).name());

        auto &it = std::find_if(this->_systems.begin(), this->_systems.end(), [&name](std::unique_ptr<ISystem> &system)
        {
            return system->GetName() == name;
        });

        return it != this->_systems.end();
    }
}