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
    class ASystem
    {
        private:
            std::vector<std::string> _dependencies;
            bool _enabled;
        protected:
            template<typename T>
            void AddDependency()
            {
                this->_dependencies.push_back(std::string(typeid(T).name()));
            }
        public:
            ASystem();
            ASystem(bool enabled = true);
            virtual ~ASystem() = default;

            virtual void Update(double, Entity &);
            virtual void OnDisable();
            virtual void OnEnable();
            const std::vector<std::string> &GetDependencies() const;
            bool GetStatus() const;
            void ToggleStatus();
    };
}

#endif /* !ASYSTEM_HPP_ */
