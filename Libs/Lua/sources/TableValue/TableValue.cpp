/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** TableValue
*/

#include "TableValue.hpp"
#include "Exceptions.hpp"

namespace Lua
{
    TableValue<std::string> Object::operator[](std::string key)
    {
        if (!this->IsTable())
            throw Exception::TableValueException("This object is not a Lua Table");
        return TableValue<std::string>(this->_state, this->_pos, key);
    }

    TableValue<int> Object::operator[](int key)
    {
        if (!this->IsTable())
            throw Exception::TableValueException("This object is not a Lua Table");
        return TableValue<int>(this->_state, this->_pos, key);
    }
}