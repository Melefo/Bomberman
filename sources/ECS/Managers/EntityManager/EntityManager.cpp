/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** EntityManager
*/

#include "Exceptions.hpp"
#include "EntityManager.hpp"

namespace ECS
{
    EntityManager::EntityManager() :
    _available(), _max(1)
    { }

    Entity EntityManager::CreateEntity()
    {
        Entity entity;

        if (this->_available.size() == 0)
            entity = this->_max++;
        else
        {
            entity = this->_available.back();
            this->_available.pop_back();
        }

        return entity;
    }

    void EntityManager::DeleteEntity(Entity entity)
    {
        if (entity >= this->_max)
            throw new Exception::EntityManagerException("This entity doesn't exists");
        this->_available.push_back(entity);
    }
}