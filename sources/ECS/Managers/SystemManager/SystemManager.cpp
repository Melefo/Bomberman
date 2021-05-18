/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** SystemManager
*/

#include "Exceptions.hpp"
#include "SystemManager.hpp"

namespace ECS
{
    template<typename T>
    std::shared_ptr<T> SystemManager::AddSystem()
    {
        std::string name(typeid(T).name);

        if (this->_systems.find(name) != this->_systems.end())
            throw new Exception::SystemManagerException("Cannot add more than once a system.");

        std::shared_ptr<T> system = std::make_shared<T>();

        this->_systems.insert(name, system);
        return system;
    }
}