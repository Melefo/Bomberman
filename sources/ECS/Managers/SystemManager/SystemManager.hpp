/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** SystemManager
*/

#ifndef SYSTEMMANAGER_HPP_
#define SYSTEMMANAGER_HPP_

#include <memory>
#include <vector>
#include "ISystem.hpp"

namespace ECS
{
    class SystemManager
    {
        private:
            std::vector<std::unique_ptr<ISystem>> _systems;
        public:
            SystemManager() = default;
            ~SystemManager() = default;

            template<typename T>
            void AddSystem();
            template<typename T>
            void RemoveSystem();
            template<typename T>
            bool HasSystem();
    };
}

#endif /* !SYSTEMMANAGER_HPP_ */
