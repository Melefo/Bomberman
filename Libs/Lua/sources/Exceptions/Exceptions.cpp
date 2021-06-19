/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Exceptions
*/

#include "Exceptions.hpp"

namespace Lua::Exception
{
    TableValueException::TableValueException(std::string value) :
    _value(value)
    {}

    const char *TableValueException::what() const noexcept
    {
        return this->_value.c_str();
    }

}