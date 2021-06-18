/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** ASystem
*/

#ifndef ASYSTEM_HPP_
#define ASYSTEM_HPP_

#include <string>
#include <vector>
#include "Entity.hpp"

namespace ECS
{
    /**
     * @brief Base Abstract class to create a new System
     * 
     */
    class ASystem
    {
        private:
            /**
             * @brief List of Components on which the System is dependent
             * 
             */
            std::vector<std::string> _dependencies;
            /**
             * @brief Toggle if the system must be updated or not
             * 
             */
            bool _enabled;
        protected:
            /**
             * @brief Add a component to list of dependencies
             * 
             * @tparam T Type of the component
             */
            template<typename T>
            void AddDependency()
            {
                this->_dependencies.push_back(std::string(typeid(T).name()));
            }
        public:
            /**
             * @brief Construct a new ASystem object
             * 
             */
            ASystem();
            /**
             * @brief Construct a new ASystem object
             * 
             * @param enabled Default value if the System is enabled or not
             */
            ASystem(bool enabled);
            /**
             * @brief Destroy the ASystem object
             * 
             */
            virtual ~ASystem() = default;
            /**
             * @brief Copy a new ASystem object
             * 
             */
            ASystem(const ASystem&) = delete;
            /**
             * @brief Assign a new ASystem Object
             * 
             * @return ASystem& Assigned ASystem
             */
            ASystem& operator=(const ASystem&) = delete;

            /**
             * @brief Update an Entity and its components
             * 
             * @param dt DeltaTime since the last Update
             * @param entity Entity to update
             */
            virtual void Update(double dt, Entity& entity);
            /**
             * @brief Update an Entity and its components at a fixed time
             * 
             * @param entity Entity to update
             */
            virtual void FixedUpdate(Entity& entity);
            /**
             * @brief Update an Entity and its components after the others
             * 
             * @param dt DeltaTime since the last Update
             * @param entity Entity to update
             */
            virtual void LateUpdate(double dt, Entity& entity);
            /**
             * @brief Event launched when the system is disabled
             * 
             */
            virtual void OnDisable();
            /**
             * @brief Event launched when the system is enabled
             * 
             */
            virtual void OnEnable();
            /**
             * @brief Get the Dependencies object
             * 
             * @return const std::vector<std::string>& List of components dependencies of the system
             */
            const std::vector<std::string>& GetDependencies() const;
            /**
             * @brief Get the Status object
             * 
             * @return true The sysetm is enabled
             * @return false The system is disabled
             */
            bool GetStatus() const;
            /**
             * @brief Set the Status object
             * 
             * @param bool new status
             */
            void SetStatus(bool newStatus);
            /**
             * @brief Enable/Disable the system
             * 
             */
            void ToggleStatus();
    };
}

#endif /* !ASYSTEM_HPP_ */
