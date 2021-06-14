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
}