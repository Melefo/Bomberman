/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include <string>

namespace ECS
{
    class ISystem
    {
        public:
            ISystem() = default;
            virtual ~ISystem() = default;

            virtual const std::string GetName() const = 0;
    };
}

#endif /* !ISYSTEM_HPP_ */
