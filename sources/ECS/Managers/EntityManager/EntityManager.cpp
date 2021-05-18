/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** EntityManager
*/

#include "EntityManager.hpp"

namespace ECS
{
    template<typename T>
    std::shared_ptr<T> EntityManager::AddEntity()
    {
        std::shared_ptr<T> entity = std::make_shared<T>();

        this->_entities.push_back(entity);
        return entity;
    }
}