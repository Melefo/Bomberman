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
    /**
     * @brief Class used to manipulate Systems
     * 
     */
    class SystemManager
    {
        private:
            /**
             * @brief List of currently created Systems
             * 
             */
            std::unordered_map<std::string, std::unique_ptr<ASystem>> _systems;
        public:
            /**
             * @brief Construct a new System Manager object
             * 
             */
            SystemManager() = default;
            /**
             * @brief Destroy the System Manager object
             * 
             */
            ~SystemManager() = default;
            /**
             * @brief Copy a new System Manager object
             * 
             */
            SystemManager(const SystemManager&) = delete;
            /**
             * @brief Assign a new SystemManager Object
             * 
             * @return SystemManager& Assigned SystemManager
             */
            SystemManager& operator=(const SystemManager&) = delete;

            /**
             * @brief Add a system to update entities
             * 
             * @tparam T Type of the system to add
             * @tparam TArgs Types of constructor arguments of T
             * @param args Constructor arguments
             * @return T& Newly added System
             */
            template<typename T, typename... TArgs>
            T& AddSystem(TArgs&&... args)
            {
                std::string name(typeid(T).name());

                if (this->HasSystem<T>())
                    throw Exception::SystemManagerException("Cannot add more than once system " + name);

                this->_systems[name] = std::make_unique<T>(std::forward<TArgs>(args)...);
                return dynamic_cast<T &>(*this->_systems[name]);
            }
            /**
             * @brief Remove a system from the list which updates entities
             * 
             * @tparam T Type of the system to remove
             */
            template<typename T>
            void RemoveSystem()
            {
                std::string name(typeid(T).name());

                const auto &it = this->_systems.find(name);
                if (it != this->_systems.end())
                    this->_systems.erase(it);
            }
            /**
             * @brief Check if the Manager contains a system
             * 
             * @tparam T Type of the System
             * @return true The Manager contains the system
             * @return false The Manager doesn't contains the system
             */
            template<typename T>
            bool HasSystem()
            {
                std::string name(typeid(T).name());

                const auto &it = this->_systems.find(name);
                return it != this->_systems.end();
            }

            /**
             * @brief Get a System from Manager
             *
             * @return T& The System
             */
            template<typename T>
            T& GetSystem()
            {
                std::string name(typeid(T).name());

                const auto& it = this->_systems.find(name);
                if (it == this->_systems.end())
                    throw Exception::EntityException("System " + name + " is not added");
                return dynamic_cast<T&>(*it->second);
            }
            /**
             * @brief Get the Systems object
             * 
             * @return const std::unordered_map<std::string, std::unique_ptr<ASystem>>& List of added Systems
             */
            const std::unordered_map<std::string, std::unique_ptr<ASystem>>& GetSystems() const;
    };
}

#endif /* !SYSTEMMANAGER_HPP_ */
