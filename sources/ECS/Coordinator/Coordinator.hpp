/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Coordinator
*/

#ifndef COORDINATOR_HPP_
#define COORDINATOR_HPP_

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
            Coordinator();
            ~Coordinator() = default;
    };
}

#endif /* !COORDINATOR_HPP_ */
