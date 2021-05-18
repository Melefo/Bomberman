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
#include "ComponentManager.hpp"

namespace ECS
{
    class Coordinator
    {
        private:
            SystemManager _systemManager;
            EntityManager _entityManager;
            ComponentManager _componentManager;
        public:
            Coordinator() = default;
            ~Coordinator() = default;
    
            template<typename T>
            std::shared_ptr<T> AddSystem();
            Entity AddEntity();
            template<typename T>
            std::shared_ptr<T> AddComponent();
            template<typename T>
            std::shared_ptr<T> GetComponent();
    };
}

#endif /* !COORDINATOR_HPP_ */
