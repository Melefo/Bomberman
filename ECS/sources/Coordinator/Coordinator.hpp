/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Coordinator
*/

#ifndef COORDINATOR_HPP_
#define COORDINATOR_HPP_

#include <memory>
#include "SystemManager.hpp"
#include "EntityManager.hpp"

namespace ECS
{
    class Coordinator
    {
        private:
            SystemManager _systemManager;
            EntityManager _entityManager;
            double _dt = 0.0f;
        public:
            Coordinator() = default;
            ~Coordinator() = default;
    
            template<typename T, typename... TArgs>
            T &AddSystem(TArgs&&... args)
            {
                return this->_systemManager.AddSystem<T>(std::forward<TArgs>(args)...);
            }
            Entity &CreateEntity();
            template<typename T>
            void RemoveSystem()
            {
                this->_systemManager.RemoveSystem<T>();
            }
            void DeleteEntity(Entity &entity);
            void Update();

            const std::vector<std::unique_ptr<Entity>>& GetEntities() const;

    };
}

#endif /* !COORDINATOR_HPP_ */
