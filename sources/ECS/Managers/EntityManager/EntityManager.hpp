/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <queue>
#include <cinttypes>

#define Entity uint32_t

namespace ECS
{
    class EntityManager
    {
        private:
            std::vector<Entity> _available; 
            Entity _max;
        public:
            EntityManager();
            ~EntityManager() = default;

            Entity CreateEntity();
            void DeleteEntity(Entity entity);
    };
}

#endif /* !ENTITYMANAGER_HPP_ */
