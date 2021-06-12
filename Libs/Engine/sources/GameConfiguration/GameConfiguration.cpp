/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** GameConfiguration
*/

#include "GameConfiguration.hpp"
#include <iostream>

namespace Engine
{
    int GameConfiguration::_players = 0;
    int GameConfiguration::_enemies = 0;
    std::map<int, playerkeys> GameConfiguration::_playerKeys = {};

    playerkeys::playerkeys(RayLib::Input input, int key) :
    movementInput(input), actionKey(key)
    {

    }

    playerkeys& GameConfiguration::GetPlayerKeys(int player)
    {
        if (player > _players)
            throw Engine::Exception::EngineException("There are only " + std::to_string(player) + " players");
        if (player < 1)
            throw Engine::Exception::EngineException("Invalid player index");
        return (_playerKeys[player]);
    }

    int GameConfiguration::GetPlayers(void)
    {
        return (_players);
    }

    void GameConfiguration::SetPlayers(int playersTotal)
    {
        //if (_playerKeys.size() != static_cast<std::size_t>(playersTotal))
        //    _playerKeys.resize(playersTotal, playerkeys());
        _players = playersTotal;
    }

    void GameConfiguration::SetPlayerKeys(int player, RayLib::Input& input, int actionKey)
    {
        if (player > _players)
            throw Engine::Exception::EngineException("There are only " + std::to_string(player) + " players");

        if (player < 1)
            throw Engine::Exception::EngineException("Invalid player index:");

        _playerKeys[player] = playerkeys(RayLib::Input(input), actionKey);
    }

    int GameConfiguration::GetEnemies(void)
    {
        return (_enemies);
    }

    void GameConfiguration::SetEnemies(int total)
    {
        _enemies = total;
    }
}