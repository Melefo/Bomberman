/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Exception
*/

#include "Exceptions.hpp"

namespace ECS::Exception
{
    AssetException::AssetException(std::string value) :
    _value(value)
    {}

    const char *AssetException::what() const noexcept
    {
        return this->_value.c_str();
    }

    AssetManagerException::AssetManagerException(std::string value) :
    _value(value)
    {}

    const char *AssetManagerException::what() const noexcept
    {
        return this->_value.c_str();
    }

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
}