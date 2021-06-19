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
#include "lua.hpp"
#include "Vector2.hpp"
#include "Exceptions.hpp"

namespace Lua
{
    struct close
    {
        void operator()(lua_State *ls)
        {
            lua_close(ls);
        }
    };

    template<typename T>
    struct is_rayvector
    {
        static constexpr bool value = false;
    };

    template<typename Value>
    struct is_rayvector<RayLib::Vector2<Value>>
    {
        static constexpr bool value = true;
    };
    
    template<typename T>
    struct is_vector
    {
        static constexpr bool value = false;
    };

    template<typename Value>
    struct is_vector<std::vector<Value>>
    {
        static constexpr bool value = true;
    };

    template <typename T>
    struct is_map
    {
        static constexpr bool value = false;
    };

    template<typename Key, typename Value>
    struct is_map<std::map<Key, Value>>
    {
        static constexpr bool value = true;
    };

    class Object;

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

                return this->Pop<T>(-1);
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
                lua_pushnumber(this->_ls.get(), static_cast<lua_Number>(t));
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
             * @brief Push a map to Lua
             * 
             * @tparam T 
             * @param map 
             */
            template<typename T>
            void Push(RayLib::Vector2<T> vec);

            template <typename T>
            typename std::enable_if<is_vector<T>::value, T>::type
                Pop(int index);

            template <typename T>
            typename std::enable_if<is_map<T>::value, T>::type
                Pop(int index);

            template <typename T>
            typename std::enable_if<is_rayvector<T>::value, T>::type
                Pop(int index);

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

            template<typename T>
            typename std::enable_if<std::is_same<T, lua_CFunction>::value, T>::type
            Pop(int index)
            {
                return lua_tocfunction(this->_ls.get(), index);
            }

            template<typename T>
            typename std::enable_if<std::is_same<T, void>::value, T>::type
            Pop(int)
            {
            }

            /**
             * @brief Get the Lua State object
             * 
             * @return std::unique_ptr<lua_State, close>& 
             */
            std::unique_ptr<lua_State, close>& GetLuaState();
    };

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

            template<typename U>
            U Cast() const;

            /**
             * @brief Get Lua Object
             * 
             * @return Object 
             */
            Object Get() const;

            /**
             * @brief Check if value is Null
             * 
             * @return true 
             * @return false 
             */
            bool Exists() const;

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
             * @brief 
             * 
             * @return int 
             */
            int Length() const;

            template<typename T>
            T Cast() const;

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
            TableValue<std::size_t> operator[](std::size_t key);
        private:
            /**
             * @brief Reference to Lua Stack State
             * 
             */
            State& _state;
            /**
             * @brief Position in the stack
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
}

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

template<typename T>
void Lua::State::Push(RayLib::Vector2<T> vec)
{
    this->CreateTable();
    Object table(*this);

    table["x"] = vec.x;
    table["y"] = vec.y;
}

template <typename T>
typename std::enable_if<Lua::is_vector<T>::value, T>::type
Lua::State::Pop(int index)
{
    T vec;

    Object table(*this, index);
    int size = table.Length();

    for (int i = 0; i < size; i++)
        vec.push_back(table[i + 1].Cast<typename T::value_type>());

    return vec;
}

template <typename T>
typename std::enable_if<Lua::is_map<T>::value, T>::type
Lua::State::Pop(int index)
{
    T map;
    index = lua_absindex(this->_ls.get(), index);
    Object table(*this, index);

    lua_pushnil(this->_ls.get());
    DelayedPop delayed(*this, 1);
    while (lua_next(this->_ls.get(), index)) {
        DelayedPop pop(*this, 1);
        std::string key = this->Pop<std::string>(-2);
        typename T::mapped_type value = this->Pop<typename T::mapped_type>(-1);
        
        map[key] = value;
        lua_pop(this->_ls.get(), 2);
        pop.SetNbr(0);
        this->Push(key);
    }

    delayed.SetNbr(0);
    return map;
}

template <typename T>
typename std::enable_if<Lua::is_rayvector<T>::value, T>::type
Lua::State::Pop(int index)
{
    T vec;
    std::map<std::string, typename T::value_type> map = this->Pop<std::map<std::string, typename T::value_type>>(index);

    vec.x = map["x"];
    vec.y = map["y"];

    return vec;
}

template<typename T>
template<typename U>
U Lua::TableValue<T>::Cast() const
{
    DelayedPop delayed(this->_state, 1);
    return this->Get().template Cast<U>();
}

template<typename T>
Lua::Object Lua::TableValue<T>::Get() const
{
    this->_state.Push(this->_key);
    lua_gettable(this->_state.GetLuaState().get(), this->_pos);

    return Object(this->_state, -1);
}

template<typename T>
bool Lua::TableValue<T>::Exists() const
{
    DelayedPop delayed(this->_state, 1);
    Object obj = this->Get();

    return !obj.IsNil();
}

template<typename T>
T Lua::Object::Cast() const
{
    return this->_state.Pop<T>(this->_pos);
}

#endif /* !LUA_HPP_ */
