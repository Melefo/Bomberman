/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** EntityManager
*/

#include <algorithm>
#include "Exceptions.hpp"
#include "EntityManager.hpp"

#include <iostream>

namespace ECS
{
    EntityManager::EntityManager() :
    _available(), _max(1)
    { }

    Entity &EntityManager::CreateEntity()
    {
        if (this->_available.size() == 0)
        {
            this->_entities.emplace_back(std::make_unique<Entity>(this->_max++));
            return *this->_entities.back();
        }
        uint32_t id = this->_available.back();

        this->_entities.emplace_back(std::make_unique<Entity>(id));
        this->_available.pop_back();
        return *this->_entities.back();
    }


    void EntityManager::DeleteEntity(Entity &entity)
    {
        for (auto it = this->_entities.begin(); it != this->_entities.end(); it++)
            if ((*it)->GetId() == entity.GetId())
            {
                this->_available.push_back(entity.GetId());
                this->_entities.erase(it);
                return;
            }
    }

    const std::vector<std::unique_ptr<Entity>> &EntityManager::GetEntities() const
    {
        return this->_entities;
    }
}