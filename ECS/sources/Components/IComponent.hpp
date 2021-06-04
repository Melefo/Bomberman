/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

namespace ECS
{
    /**
     * @brief Base Interface class to create a new component
     * 
     */
    class IComponent
    {
        public:
            /**
             * @brief Construct a new IComponent object
             * 
             */
            IComponent() = default;
            /**
             * @brief Destroy the IComponent object
             * 
             */
            virtual ~IComponent() = default;
            /**
             * @brief Copy a new IComponent object
             * 
             */
            IComponent(const IComponent&) = delete;
            /**
             * @brief Assign a new IComponent object
             * 
             * @return IComponent& assigned component
             */
            IComponent& operator=(const IComponent&) = delete;
    };
}

#endif /* !ICOMPONENT_HPP_ */