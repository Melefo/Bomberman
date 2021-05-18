/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Exception
*/

#include "Exceptions.hpp"

namespace ECS::Exception
{
    SystemManagerException::SystemManagerException(std::string value) :
    _value(value)
    {}

    const char *SystemManagerException::what() const noexcept
    {
        return this->_value.c_str();
    }

    ComponentManagerException::ComponentManagerException(std::string value) :
    _value(value)
    {}

    const char *ComponentManagerException::what() const noexcept
    {
        return this->_value.c_str();
    }
}