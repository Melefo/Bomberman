/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** EngineExceptions
*/

#include "EngineExceptions.hpp"

namespace Engine::Exception
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
}
