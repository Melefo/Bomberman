/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <cinttypes>
#include <unordered_map>
#include <memory>
#include "IComponent.hpp"

namespace ECS
{
    class Entity
    {
        private:
            uint32_t _id;
            std::unordered_map<std::string, std::unique_ptr<IComponent>> _components;

        public:
            Entity(uint32_t id);
            ~Entity() = default;
            template<typename T>
            std::unique_ptr<T> &GetComponent();
            template<typename T>
            void AddComponent();
            template<typename T>
            bool HasComponent() const;
            bool HasComponent(std::string &name) const;
            uint32_t GetId() const;
    };
}

#endif /* !ENTITY_HPP_ */
