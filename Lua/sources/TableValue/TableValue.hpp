/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** TableValue
*/

#ifndef TABLEVALUE_HPP_
#define TABLEVALUE_HPP_

#include "State.hpp"
#include "Object.hpp"

namespace Lua
{
    /**
     * @brief Value from Lua Table
     * 
     * @tparam T 
     */
    template<typename T>
    class TableValue
    {
        public:
            /**
             * @brief Construct a new Table Value object
             * 
             * @param state 
             * @param pos 
             * @param key 
             */
            TableValue(State& state, int pos, T key) :
            _state(state), _pos(pos), _key(key)
            {}
            /**
             * @brief Destroy the Table Value object
             * 
             */
            ~TableValue() = default;
            /**
             * @brief Copy a new Table Value object
             * 
             */
            TableValue(const TableValue&) = delete;
            /**
             * @brief Assign a new TableValue
             * 
             * @return TableValue& assigned TableValue
             */
            TableValue& operator=(const TableValue&) = delete;

            /**
             * @brief Set value inside Table child
             * 
             * @tparam U 
             * @param value 
             * @return TableValue& 
             */
            template<typename U>
            TableValue& operator=(U&& value)
            {
                return this->Set<U>(value);
            }

            /**
             * @brief Set key & value to lua Table child
             * 
             * @tparam U 
             * @param value 
             * @return TableValue& 
             */
            template<typename U>
            TableValue& Set(U&& value)
            {
                this->_state.Push(this->_key);
                this->_state.Push(std::forward<U>(value));

                lua_settable(this->_state.GetLuaState().get(), this->_pos);
                return *this;
            }

            /*template<typename U>
            U Cast() const
            {
                DelayedPop delayed(this->_state, 1);
                Object obj = this->Get();

                return obj.Cast<U>();
            }*/

            /**
             * @brief Get Lua Object
             * 
             * @return Object 
             */
            Object Get() const
            {
                this->_state.Push(this->_key);
                lua_gettable(this->_state.GetLuaState().get(), this->_pos);

                return Object(this->_state, -1);
            }

            /**
             * @brief Check if value is Null
             * 
             * @return true 
             * @return false 
             */
            bool Exists() const
            {
                DelayedPop delayed(this->_state, 1);
                Object obj = this->Get();

                return !obj.IsNil();
            }
        private:
            /**
             * @brief Reference to Lua Stack
             * 
             */
            State& _state;
            /**
             * @brief Position of the value inside the table
             * 
             */
            int _pos;
            /**
             * @brief Key associated with the value
             * 
             */
            T _key;
    };
}

#endif /* !TABLEVALUE_HPP_ */
