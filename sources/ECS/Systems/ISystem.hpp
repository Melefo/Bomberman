/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include <string>
#include <vector>
#include "Entity.hpp"

namespace ECS
{
    class ISystem
    {
        public:
            ISystem() = default;
            virtual ~ISystem() = default;

            virtual void Update(double dt, Entity &entity) = 0;
            virtual const std::vector<std::string> GetDependencies() const = 0;
    };
}

#endif /* !ISYSTEM_HPP_ */
