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
#include "EntityManager.hpp"
#include "IComponent.hpp"

namespace ECS
{
    /**
     * @brief Scene object containing components and an ID
     * 
     */
    class Entity
    {
        private:
            /**
             * @brief ID of the Entity
             * 
             */
            uint32_t _id;

            /**
             * @brief Manage components inside the Entity
             * 
             */
            ComponentManager _componentManager;
            /**
             * @brief Reference to the Scene in which it has been created
             * 
             */
            EntityManager& _entityManager;
            /**
             * @brief Entity's tag
             * Equal to "Untagged" by default
             */
            std::string _tag;
        public:
            /**
             * @brief Construct a new Entity object
             * 
             */
            Entity() = delete;
            /**
             * @brief Construct a new Entity object
             * 
             * @param id ID for the new Entity
             * @param entityManager Reference to the scene
             */
            Entity(uint32_t id, EntityManager& entityManager, const std::string& tag="Untagged");
            /**
             * @brief Destroy the Entity object
             * 
             */
            ~Entity() = default;
            /**
             * @brief Copy a new Entity object
             * 
             */
            Entity(const Entity&) = delete;
            /**
             * @brief Assign a new Entity Object
             * 
             * @return Entity& assigned Entity
             */
            Entity& operator=(const Entity&) = delete;

            /**
             * @brief Get the Component object
             * 
             * @tparam T Type of the Component
             * @return T& reference to the Component
             */
            template<typename T>
            T& GetComponent()
            {
                return this->_componentManager.GetComponent<T>();
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
                return this->_componentManager.OfType<T>();
            }

            /**
             * @brief Get the Components object
             * 
             * @return std::vector<std::unique_ptr<IComponent>&> 
             */
            std::vector<std::reference_wrapper<std::unique_ptr<IComponent>>> GetComponents();

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
                this->_componentManager.AddComponent<T>(std::forward<TArgs>(args)...);
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
                this->_componentManager.AddComponent<Base, T>(std::forward<TArgs>(args)...);
            }
            /**
             * @brief Remove a Component from the Entity
             * 
             * @tparam T Type of the Component
             */
            template<typename T>
            void RemoveComponent()
            {
                this->_componentManager.RemoveComponent<T>();
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
                return this->_componentManager.HasComponent<T>();
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
            /**
             * @brief Get the Id object
             * 
             * @return uint32_t Current ID of the Entity
             */
            uint32_t GetId() const;
            /**
             * @brief Remove the Component from the scene and so destroy itself
             * 
             */
            void Dispose();

            /**
             * @brief Get Component by name, if exists
             * 
             */
            IComponent& GetComponentByName(const std::string& name);

            void SetTag(const std::string& tag);
            const std::string& GetTag(void) const;


    };
}

#endif /* !ENTITY_HPP_ */
