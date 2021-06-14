/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Object
*/

#include "TableValue.hpp"
#include "DelayedPop.hpp"
#include "Object.hpp"

namespace Lua
{
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
} // namespace Lua