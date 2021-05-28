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
#include <algorithm>
#include <vector>
#include "Exceptions.hpp"
#include "ComponentManager.hpp"
#include "IComponent.hpp"

namespace ECS
{
    class Entity
    {
        private:
            uint32_t _id;
            ComponentManager _componentManager;
        public:
            Entity(uint32_t id);
            ~Entity() = default;
            template<typename T>
            T &GetComponent()
            {
                return this->_componentManager.GetComponent<T>();
            }
            template<typename T>
            std::vector<std::reference_wrapper<T>> &OfType()
            {
                return this->_componentManager.OfType<T>();
            }
            template<typename T, typename... TArgs>
            void AddComponent(TArgs&&... args)
            {
                this->_componentManager.AddComponent<T>(std::forward<TArgs>(args)...);
            }
            template<typename T>
            void RemoveComponent()
            {
                this->_componentManager.RemoveComponent<T>();
            }
            template<typename T>
            bool HasComponent() const
            {
                return this->_componentManager.HasComponent<T>();
            }
            bool HasComponent(std::string &name) const;
            bool HasComponents(std::vector<std::string> &names) const;
            uint32_t GetId() const;
    };
}

#endif /* !ENTITY_HPP_ */
