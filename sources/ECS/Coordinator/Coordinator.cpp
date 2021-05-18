/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Coordinator
*/

#include "Coordinator.hpp"

namespace ECS
{
    template<typename T>
    std::shared_ptr<T> Coordinator::AddSystem()
    {
        return this->_systemManager.AddSystem<T>();
    }

    template<typename T>
    std::shared_ptr<T> Coordinator::AddEntity()
    {
        return this->_entityManager.AddEntity<T>();
    }
}