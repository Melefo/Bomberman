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
#include <list>

namespace ECS
{
    class Entity;

    /**
     * @brief Class used to manipulate Entities (a.k.a A Scene)
     * 
     */
    class EntityManager
    {
        private:
            /**
             * @brief List of ID detroyed and available to new Entities
             * 
             */
            std::vector<uint32_t> _available;
            /**
             * @brief Last ID given to an Entity
             * 
             */
            uint32_t _max;
            /**
             * @brief List of currently created Entities
             * 
             */
            std::list<std::unique_ptr<Entity>> _entities;
        public:
            /**
             * @brief Construct a new Entity Manager object
             * 
             */
            EntityManager();
            /**
             * @brief Destroy the Entity Manager object
             * 
             */
            ~EntityManager() = default;
            /**
             * @brief Copy a new Entity Manager object
             * 
             */
            EntityManager(const EntityManager&) = default;
            /**
             * @brief Assign a new EntityManager Object
             * 
             * @return EntityManager& assigned EntityManager
             */
            EntityManager& operator=(const EntityManager&) = default;

            /**
             * @brief Create a Entity object
             * 
             * @return Entity& newly created entity
             */
            Entity& CreateEntity();
            /**
             * @brief Delete an Entity from the scene
             * 
             * @param entity Entity to destroy
             */
            void DeleteEntity(Entity& entity);
            /**
             * @brief Get the Entities object
             * 
             * @return const std::vector<std::unique_ptr<Entity>>& list of the entities created
             */
            //const std::vector<std::unique_ptr<Entity>>& GetEntities() const;
            const std::list<std::unique_ptr<Entity>>& GetEntities() const;
    };
}

#endif /* !ENTITYMANAGER_HPP_ */
