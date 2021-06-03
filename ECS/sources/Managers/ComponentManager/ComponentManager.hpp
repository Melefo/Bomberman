/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** ComponentManager
*/

#ifndef COMPONENTMANAGER_HPP_
#define COMPONENTMANAGER_HPP_

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "Exceptions.hpp"
#include "IComponent.hpp"

namespace ECS
{
    /**
     * @brief Class used to manipulate Components
     * 
     */
    class ComponentManager
    {
        private:
            /**
             * @brief Map associating a base component with its derived
             * 
             */
            std::unordered_map<std::string, std::vector<std::string>> _bases;
            /**
             * @brief List of currently created Components
             * 
             */
            std::unordered_map<std::string, std::unique_ptr<IComponent>> _components;
        public:
            /**
             * @brief Construct a new Component Manager object
             * 
             */
            ComponentManager();
            /**
             * @brief Destroy the Component Manager object
             * 
             */
            ~ComponentManager() = default;
            /**
             * @brief Copy a new Component Manager object
             * 
             */
            ComponentManager(const ComponentManager&) = delete;
            /**
             * @brief Assign a new ComponentManager Object
             * 
             * @return ComponentManager& Assigned Entity
             */
            ComponentManager& operator=(const ComponentManager&) = delete;

            /**
             * @brief Get the Component object
             * 
             * @tparam T Type of the Component
             * @return T& Reference to the Component
             */
            template<typename T>
            T& GetComponent()
            {
                std::string name(typeid(T).name());

                const auto &it = this->_components.find(name);
                if (it == this->_components.end())
                    throw Exception::EntityException("Entity doesn't contains this Component");
                return dynamic_cast<T &>(*it->second);
            }
            /**
             * @brief Get every Component derivating from T
             * 
             * @tparam T base class of the Components
             * @return std::vector<std::reference_wrapper<T>> List of references to Components
             */
            template<typename T>
            std::vector<std::reference_wrapper<T>> OfType()
            {
                std::string baseName(typeid(T).name());
                std::vector<std::reference_wrapper<T>> list;
                const auto &it = this->_bases.find(baseName);

                if (it == this->_bases.end())
                    return list;
                for (std::string& name : it->second)
                    list.push_back(dynamic_cast<T&>(*this->_components[name]));
                return list;
            }
            /**
             * @brief Add a new Component to the current Entity
             * 
             * @tparam T Type of the Component
             * @tparam TArgs Types of the constructor arguments of the Component
             * @param args Constructor arguments of the Component
             */
            template<typename T, typename... TArgs>
            void AddComponent(TArgs&&... args)
            {
                std::string name(typeid(T).name());

                if (this->HasComponent<T>())
                    throw Exception::EntityException("Entity already contains this Component");
                this->_components[name] = std::make_unique<T>(std::forward<TArgs>(args)...);
            }
            /**
             * @brief Add a new derived Component to the current Entity
             * 
             * @tparam Base Base class of the Component
             * @tparam T Derived class of the Component
             * @tparam TArgs Types of the constructor arguments of the Component
             * @param args Constructor arguments of the Component
             */
            template<typename Base, typename T, typename... TArgs>
            void AddComponent(TArgs&&... args)
            {
                static_assert(std::is_base_of<Base, T>::value, "Class doesn't inherit from Base");
                std::string name(typeid(T).name());

                if (this->HasComponent<T>())
                    throw Exception::EntityException("Entity already contains this Component");
                this->_components[name] = std::make_unique<T>(std::forward<TArgs>(args)...);

                std::string baseName(typeid(Base).name());

                if (this->_bases.find(baseName) == this->_bases.end())
                    this->_bases[baseName] = std::vector<std::string>();
                this->_bases[baseName].push_back(name);
            }
            /**
             * @brief Remove a Component from the Entity
             * 
             * @tparam T Type of the Component
             */
            template<typename T>
            void RemoveComponent()
            {
                std::string name(typeid(T).name());

                const auto &it = this->_components.find(name);

                if (it == this->_components.end())
                    return;
                for (auto base = this->_bases.begin(); base != this->_bases.end(); base++)
                {
                    const auto &found = std::find(base->second.begin(), base->second.end(), it->first);
                    if (found != base->second.end())
                        base->second.erase(found);
                    if (base->second.size() == 0)
                        this->_bases.erase(base->first);
                }
                this->_components.erase(it);
            }
            /**
             * @brief Check if the Entity contains a given Component
             * 
             * @tparam T type of the Component
             * @return true The Entity contains the component
             * @return false The Entity doesn't contains the component
             */
            template<typename T>
            bool HasComponent() const
            {
                std::string name(typeid(T).name());

                return this->_components.find(name) != this->_components.end();
            }
            /**
             * @brief Check if the Entity contains a given Component based on its name
             * 
             * @param name Name of the component
             * @return true The Entity contains the component
             * @return false The Entity doesn't Contains the component
             */
            bool HasComponent(std::string &name) const;
            /**
             * @brief Check if the Entity contains a list of given Component based on teirs names
             * 
             * @param names List of Component names
             * @return true The entity contains every Components
             * @return false The entity is missing at least Component
             */
            bool HasComponents(std::vector<std::string> &names) const;
    };
}

#endif /* !COMPONENTMANAGER_HPP_ */
