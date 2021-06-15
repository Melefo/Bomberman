/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** lua
*/

#include <fstream>
#include <sstream>
#include "State.hpp"

namespace Lua
{
    State::State() : _ls(luaL_newstate())
    {
        luaL_openlibs(this->_ls.get());
    }

    int State::RunScript(std::string filepath)
    {
        if (luaL_loadfile(this->_ls.get(), filepath.c_str()) == 0)
            return lua_pcall(this->_ls.get(), 0, 0, 0);
        return 1;
    }
    
    std::unique_ptr<lua_State, close>& State::GetLuaState()
    {
        return this->_ls;
    }

    void State::PushMany()
    {
        
    }

    void State::Push(lua_CFunction f)
    {
        lua_pushcfunction(this->_ls.get(), f);
    }

    void State::Push(bool b)
    {
        lua_pushboolean(this->_ls.get(), b);
    }

    void State::Push(std::string str)
    {
        lua_pushstring(this->_ls.get(), str.c_str());
    }

    void State::Push(Nil)
    {
        lua_pushnil(this->_ls.get());
    }

    TableValue<std::string> Object::operator[](std::string key)
    {
        if (!this->IsTable())
            throw Exception::TableValueException("This object is not a Lua Table");
        return TableValue<std::string>(this->_state, this->_pos, key);
    }

    TableValue<std::size_t> Object::operator[](std::size_t key)
    {
        if (!this->IsTable())
            throw Exception::TableValueException("This object is not a Lua Table");
        return TableValue<std::size_t>(this->_state, this->_pos, key);
    }

    Object::Object(State& state, int pos) :
    _state(state), _pos(lua_absindex(this->_state.GetLuaState().get(), pos))
    {

    }

    bool Object::IsNumber() const
    {
        return this->LuaType() == LUA_TNUMBER;
    }

    bool Object::IsString() const
    {
        return this->LuaType() == LUA_TSTRING;
    }

    bool Object::IsNil() const
    {
        return this->LuaType() == LUA_TNIL;
    }

    bool Object::IsBoolean() const
    {
        return this->LuaType() == LUA_TBOOLEAN;
    }

    bool Object::IsTable() const
    {
        return this->LuaType() == LUA_TTABLE;
    }

    int Object::Length() const
    {
        lua_len(this->_state.GetLuaState().get(), this->_pos);
        DelayedPop delayed(this->_state, 1);
        return this->_state.Pop<int>(-1);
    }

    int Object::LuaType() const
    {
        return lua_type(this->_state.GetLuaState().get(), this->_pos);
    }

    bool Object::operator==(const Object& obj) const
    {
        if (this->_state.GetLuaState() != obj._state.GetLuaState())
            return false;
        return lua_rawequal(this->_state.GetLuaState().get(), this->_pos, obj._pos);
    }
}