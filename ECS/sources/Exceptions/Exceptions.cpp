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

    EntityManagerException::EntityManagerException(std::string value) :
    _value(value)
    {}

    const char *EntityManagerException::what() const noexcept
    {
        return this->_value.c_str();
    }

    EntityException::EntityException(std::string value) :
    _value(value)
    {}

    const char *EntityException::what() const noexcept
    {
        return this->_value.c_str();
    }

    ComponentException::ComponentException(std::string value) :
    _value(value)
    {}

    const char *ComponentException::what() const noexcept
    {
        return this->_value.c_str();
    }
}