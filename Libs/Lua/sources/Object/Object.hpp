/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Object
*/

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <memory>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

namespace Lua
{
    template<typename T>
    class TableValue;

    class State;

    /**
     * @brief Represents a Lua object
     * 
     */
    class Object
    {
        public:
            /**
             * @brief Construct a new Object object
             * 
             * @param state 
             * @param pos 
             */
            Object(State& state, int pos = -1);
            /**
             * @brief Destroy the Object object
             * 
             */
            ~Object() = default;
            /**
             * @brief Copy a new Object object
             * 
             */
            Object(const Object&) = delete;
            /**
             * @brief Assugn a new Object object
             * 
             * @return Object& assigned Object
             */
            Object& operator=(const Object&) = delete;

            /**
             * @brief Check if a Lua Object is a number
             * 
             * @return true 
             * @return false 
             */
            bool IsNumber() const;
            /**
             * @brief Check if a Lua Object is a string
             * 
             * @return true 
             * @return false 
             */
            bool IsString() const;
            /**
             * @brief Check if a Lua Object is Null
             * 
             * @return true 
             * @return false 
             */
            bool IsNil() const;
            /**
             * @brief Check if a Lua Object is a boolean
             * 
             * @return true 
             * @return false 
             */
            bool IsBoolean() const;
            /**
             * @brief Check if a Lua Object is a table
             * 
             * @return true 
             * @return false 
             */
            bool IsTable() const;

            /**
             * @brief Return the number of items inside the table Object
             * 
             * @return int 
             */
            int Length() const;
            /*template<typename T>
            T Cast() const
            {
                return this->_state.Pop<T>(this->_pos);
            }*/

            /**
             * @brief Compare an Object with another
             * 
             * @param obj 
             * @return true 
             * @return false 
             */
            bool operator==(const Object& obj) const;
            /**
             * @brief Append an Object to a Lua Map
             * 
             * @param key 
             * @return TableValue<std::string> 
             */
            TableValue<std::string> operator[](std::string key);
            /**
             * @brief Append an Object to a Lua Vector
             * 
             * @param key 
             * @return TableValue<int> 
             */
            TableValue<int> operator[](int key);
        private:
            /**
             * @brief Reference to Lua Stack State
             * 
             */
            State& _state;
            /**
             * @brief Possition in the stack
             * 
             */
            int _pos;
            /**
             * @brief Return the type of the object from Lua
             * 
             * @return int 
             */
            int LuaType() const;
    };

} // namespace Lua

#endif /* !OBJECT_HPP_ */
