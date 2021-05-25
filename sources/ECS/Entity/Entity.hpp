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
#include "Exceptions.hpp"
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
            T &GetComponent()
            {
                std::string name(typeid(T).name());

                const auto &it = this->_components.find(name);
                if (it == this->_components.end())
                    throw new Exception::EntityException("Entity doesn't contains this Component");
                return dynamic_cast<T &>(*it->second);
            }
            template<typename T>
            void AddComponent()
            {
                std::string name(typeid(T).name());

                if (this->HasComponent<T>())
                    throw new Exception::EntityException("Entity already contains this Component");
                this->_components[name] = std::make_unique<T>();
            }
            template<typename T>
            bool HasComponent() const
            {
                std::string name(typeid(T).name());

                return this->_components.find(name) != this->_components.end();
            }
            bool HasComponent(std::string &name) const;
            uint32_t GetId() const;
    };
}

#endif /* !ENTITY_HPP_ */
