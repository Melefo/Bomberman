/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Entity
*/

#include "Entity.hpp"

namespace ECS
{
    Entity::Entity(uint32_t id) :
    _id(id), _components()
    {
    }

    bool Entity::HasComponent(std::string &name) const
    {
        return this->_components.find(name) != this->_components.end();
    }

    bool Entity::HasComponents(std::vector<std::string> &names) const
    {
        for (auto &name : names)
            if (!this->HasComponent(name))
                return false;
        return true;
    }

    uint32_t Entity::GetId() const
    {
        return this->_id;
    }
}