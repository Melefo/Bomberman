/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** SystemManager
*/

#ifndef SYSTEMMANAGER_HPP_
#define SYSTEMMANAGER_HPP_

#include <memory>
#include <unordered_map>
#include <string>
#include "ISystem.hpp"

namespace ECS
{
    class SystemManager
    {
        private:
            std::unordered_map<std::string, std::shared_ptr<ISystem>> _systems;
        public:
            SystemManager() = default;
            ~SystemManager() = default;

            template<typename T>
            std::shared_ptr<T> AddSystem();
    };
}

#endif /* !SYSTEMMANAGER_HPP_ */
