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
        protected:
            template<typename T>
            void AddDependency()
            {
                this->_dependencies.push_back(std::string(typeid(T).name()));
            }
        public:
            ASystem() = default;
            virtual ~ASystem() = default;

            virtual void Update(double, Entity &);
            const std::vector<std::string> GetDependencies() const;
    };
}

#endif /* !ASYSTEM_HPP_ */
