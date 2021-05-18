/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** AEntity
*/

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

namespace ECS
{
    class IEntity
    {
        public:
            IEntity() = default;
            virtual ~IEntity() = default;
    };
}

#endif /* !AENTITY_HPP_ */
