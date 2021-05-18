/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** ComponentManager
*/

#include "Exceptions.hpp"
#include "ComponentManager.hpp"

namespace ECS
{
    template<typename T>
    std::shared_ptr<T> ComponentManager::AddComponent()
    {
        std::string name(typeid(T).name);

        if (this->_components.find(name) != this->_components.end())
            throw new Exception::ComponentManagerException("Cannot add more than once a component.");

        std::shared_ptr<T> component = std::make_shared<T>();

        this->_components.insert(name, component);
        return component;
    }
}