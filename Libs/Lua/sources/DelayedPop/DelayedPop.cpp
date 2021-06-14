/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** DelayedPop
*/

#include "State.hpp"
#include "DelayedPop.hpp"

namespace Lua
{
    DelayedPop::DelayedPop(State& state, int nbr) :
        _state(state), _nbr(nbr)
    {
    }

    DelayedPop::~DelayedPop()
    {
        if (this->_nbr > 0)
            lua_pop(this->_state.GetLuaState().get(), this->_nbr);
    }
}