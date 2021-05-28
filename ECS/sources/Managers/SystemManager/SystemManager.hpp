/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** SystemManager
*/

#ifndef SYSTEMMANAGER_HPP_
#define SYSTEMMANAGER_HPP_

#include <memory>
#include <algorithm>
#include <string>
#include <unordered_map>
#include "ASystem.hpp"
#include "Exceptions.hpp"

namespace ECS
{
    class SystemManager
    {
        private:
            std::unordered_map<std::string, std::unique_ptr<ASystem>> _systems;
        public:
            SystemManager() = default;
            ~SystemManager() = default;

            template<typename T, typename... TArgs>
            T &AddSystem(TArgs&&... args)
            {
                std::string name(typeid(T).name());

                if (this->HasSystem<T>())
                    throw Exception::SystemManagerException("Cannot add more than once a system.");

                this->_systems[name] = std::make_unique<T>(std::forward<TArgs>(args)...);
                return dynamic_cast<T &>(*this->_systems[name]);
            }
            template<typename T>
            void RemoveSystem()
            {
                std::string name(typeid(T).name());

                const auto &it = this->_systems.find(name);
                if (it != this->_systems.end())
                    this->_systems.erase(it);
            }
            template<typename T>
            bool HasSystem()
            {
                std::string name(typeid(T).name());

                const auto &it = this->_systems.find(name);
                return it != this->_systems.end();
            }
            const std::unordered_map<std::string, std::unique_ptr<ASystem>> &GetSystems() const;
    };
}

#endif /* !SYSTEMMANAGER_HPP_ */
