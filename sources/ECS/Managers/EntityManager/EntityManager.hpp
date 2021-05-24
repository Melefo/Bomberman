/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <vector>
#include <cinttypes>
#include <memory>
#include "Entity.hpp"

namespace ECS
{
    class EntityManager
    {
        private:
            std::vector<uint32_t> _available;
            uint32_t _max;
            std::vector<std::unique_ptr<Entity>> _entities;
        public:
            EntityManager();
            ~EntityManager() = default;

            Entity &CreateEntity();
            void DeleteEntity(Entity &entity);
            const std::vector<std::unique_ptr<Entity>> &GetEntities() const;
    };
}

#endif /* !ENTITYMANAGER_HPP_ */
