/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** SystemManager
*/

#include "SystemManager.hpp"

namespace ECS
{
    const std::unordered_map<std::string, std::unique_ptr<ASystem>>& SystemManager::GetSystems() const
    {
        return this->_systems;
    }
}