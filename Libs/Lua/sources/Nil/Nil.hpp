/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Nil
*/

#ifndef NIL_HPP_
#define NIL_HPP_

namespace Lua
{
    /**
     * @brief Null equivalent to Lua
     * 
     */
    class Nil
    {
        public:
            /**
             * @brief Construct a new Nil object
             * 
             */
            Nil() = default;
            /**
             * @brief Destroy the Nil object
             * 
             */
            ~Nil() = default;
            /**
             * @brief Copy a new Nil object
             * 
             */
            Nil(const Nil&) = default;
            /**
             * @brief Assign a new Nil object
             * 
             * @return Nil& assigned Nil
             */
            Nil& operator=(const Nil&) = default;
    };
}

#endif /* !NIL_HPP_ */
