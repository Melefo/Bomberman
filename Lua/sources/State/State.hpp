/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** lua
*/

#ifndef LUA_HPP_
#define LUA_HPP_

#include <memory>
#include <map>
#include <vector>
#include <string>
#include "DelayedPop.hpp"
#include "Nil.hpp"
#include "Object.hpp"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

namespace Lua
{
    template<typename T>
    class TableValue;

    struct close
    {
        void operator()(lua_State *ls)
        {
            lua_close(ls);
        }
    };

    /**
     * @brief Lua Stack State
     * 
     */
    class State
    {
        private:
            /**
             * @brief Current state
             * 
             */
            std::unique_ptr<lua_State, close> _ls;
    
            /**
             * @brief End of Templated PushMany
             * 
             */
            void PushMany();
            /**
             * @brief Push to Lua a CPP variable
             * 
             * @tparam A1 
             * @tparam A 
             * @param first 
             * @param params 
             */
            template<typename A1, typename... A>
            void PushMany(A1&& first, A&&... params)
            {
                this->Push(std::forward<A1>(first));
                this->PushMany(std::forward<A>(params)...);
            }
            /**
             * @brief Create a Table object
             * 
             */
            void CreateTable()
            {
                lua_newtable(this->_ls.get());
            }
        public:
            /**
             * @brief Construct a new State object
             * 
             */
            State();
            /**
             * @brief Destroy the State object
             * 
             */
            ~State() = default;
            /**
             * @brief Copy a new State object
             * 
             */
            State(const State&) = delete;
            /**
             * @brief Assign a new State object
             * 
             * @return State& assgigned State
             */
            State& operator=(const State&) = delete;

            /**
             * @brief Run a .lua script
             * 
             * @param filepath 
             * @return int 
             */
            int RunScript(std::string filepath);

            /**
             * @brief Get a Lua Global variable
             * 
             * @tparam T 
             * @param name 
             * @return T 
             */
            template<typename T>
            T GetGlobal(std::string name)
            {
                lua_getglobal(this->_ls.get(), name.c_str());
                T value = this->Pop<T>(-1);
                lua_pop(this->_ls.get(), 1);

                return value;
            }
            /**
             * @brief Set a Lua Global variable
             * 
             * @tparam T 
             * @param name 
             * @param value 
             */
            template<typename T>
            void SetGlobal(std::string name, T value)
            {
                this->Push(value);
                lua_setglobal(this->_ls.get(), name.c_str());
            }
            /**
             * @brief Call a Lua function
             * 
             * @tparam T 
             * @tparam Args 
             * @param name 
             * @param args 
             * @return T 
             */
            template<typename T = void, typename... Args>
            T Call(std::string name, Args&&... args)
            {
                lua_getglobal(this->_ls.get(), name.c_str());
                this->PushMany(std::forward<Args>(args)...);
                lua_pcall(this->_ls.get(), sizeof...(args), 1, 0);
                DelayedPop delayed(*this, 1);
                T value = this->Pop<T>(-1);

                return value;
            }

            /**
             * @brief Push a C-like Function to Lua
             * 
             * @param f 
             */
            void Push(lua_CFunction f);
            /**
             * @brief Push a boolean to Lua
             * 
             * @param b 
             */
            void Push(bool b);
            /**
             * @brief Push a string to Lua
             * 
             * @param str 
             */
            void Push(std::string str);
            /**
             * @brief Push a Null to Lua
             * 
             */
            void Push(Nil);
            /**
             * @brief Push a number to Lua
             * 
             * @tparam T 
             * @param t 
             * @return std::enable_if<std::is_arithmetic<T>::value>::type 
             */
            template<typename T>
            typename std::enable_if<std::is_arithmetic<T>::value>::type
            Push(T t)
            {
                lua_pushnumber(this->_ls.get(), t);
            }
            /**
             * @brief Push a vector to Lua
             * 
             * @tparam T 
             * @param vec 
             */
            template<typename T>
            void Push(std::vector<T> vec);
            /**
             * @brief Push a map to Lua
             * 
             * @tparam T 
             * @param map 
             */
            template<typename T>
            void Push(std::map<std::string, T> map);

            /**
             * @brief Pop a bool from Lua
             * 
             * @tparam ool 
             * @param index 
             * @return true 
             * @return false 
             */
            template<typename T>
            typename std::enable_if<std::is_same<T, bool>::value, T>::type
            Pop(int index)
            {
                return lua_toboolean(this->_ls.get(), index);
            }

            /**
             * @brief Pop a number from Lua
             * 
             * @tparam T 
             * @param index 
             * @return std::enable_if<std::is_arithmetic<T>::value, T>::type 
             */
            template<typename T>
            typename std::enable_if<std::is_arithmetic<T>::value && !std::is_same<T, bool>::value, T>::type
            Pop(int index)
            {
                return static_cast<T>(lua_tonumber(this->_ls.get(), index));
            }

            /**
             * @brief Pop a string from Lua
             * 
             * @tparam T 
             * @param index 
             * @return std::enable_if<std::is_same<T, std::string>::value, T>::type 
             */
            template<typename T>
            typename std::enable_if<std::is_same<T, std::string>::value, T>::type
            Pop(int index)
            {
                return lua_tostring(this->_ls.get(), index);
            }

            /**
             * @brief Get the Lua State object
             * 
             * @return std::unique_ptr<lua_State, close>& 
             */
            std::unique_ptr<lua_State, close>& GetLuaState();
    };
}

#include "TableValue.hpp"

template<typename T>
void Lua::State::Push(std::vector<T> vec)
{
    this->CreateTable();
    Object table(*this);

    for (size_t i = 0; i < vec.size(); i++)
        table[i + 1] = vec[i];
}
template<typename T>
void Lua::State::Push(std::map<std::string, T> map)
{
    this->CreateTable();
    Object table(*this);

    for (auto it : map)
        table[it.first] = it.second;
}

#endif /* !LUA_HPP_ */
