/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <vector>
#include <memory>
#include "IEntity.hpp"

namespace ECS
{
    class EntityManager
    {
        private:
            std::vector<std::shared_ptr<IEntity>> _entities;
        public:
            EntityManager() = default;
            ~EntityManager() = default;

            template<typename T>
            std::shared_ptr<T> AddEntity();
    };
}

#endif /* !ENTITYMANAGER_HPP_ */
