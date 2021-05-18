/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** ComponentManager
*/

#ifndef COMPONENTMANAGER_HPP_
#define COMPONENTMANAGER_HPP_

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include "IComponent.hpp"

namespace ECS
{
    class ComponentManager
    {
        private:
            std::unordered_map<std::string, std::shared_ptr<IComponent>> _components;
        public:
            ComponentManager() = default;
            ~ComponentManager() = default;

            template<typename T>
            std::shared_ptr<T> AddComponent();
            template<typename T>
            std::shared_ptr<T> GetComponent();
    };
}

#endif /* !COMPONENTMANAGER_HPP_ */
