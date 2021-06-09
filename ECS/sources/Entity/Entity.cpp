/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Entity
*/

#include "Entity.hpp"

namespace ECS
{
    Entity::Entity(uint32_t id, EntityManager &entityManager, const std::string& tag) :
    _id(id), _componentManager(), _entityManager(entityManager), _tag(tag)
    {
    }

    bool Entity::HasComponent(std::string& name) const
    {
        return this->_componentManager.HasComponent(name);
    }

    bool Entity::HasComponents(std::vector<std::string>& names) const
    {
        return this->_componentManager.HasComponents(names);
    }

    uint32_t Entity::GetId() const
    {
        return this->_id;
    }

    void Entity::Dispose()
    {
        this->_entityManager.DeleteEntity(*this);
    }

    IComponent& Entity::GetComponentByName(const std::string& name)
    {
        return (this->_componentManager.GetComponentByName(name));
    }

}