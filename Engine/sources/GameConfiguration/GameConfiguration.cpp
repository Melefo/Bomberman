/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** GameConfiguration
*/

#include "GameConfiguration.hpp"

namespace Engine
{
    int GameConfiguration::_players = 0;
    int GameConfiguration::_enemies = 0;

    GameConfiguration::playerkeys& GameConfiguration::GetPlayerKeys(int player)
    {
        if (player > _players)
            throw Engine::Exception::EngineException("There are only " + std::to_string(player) + " players");
        return (_playerKeys[player]);
    }

    int GameConfiguration::GetPlayers(void)
    {
        return (_players);
    }

    void GameConfiguration::SetPlayers(int playersTotal)
    {
        _players = playersTotal;
    }

    void GameConfiguration::SetPlayerKeys(int, RayLib::Input&, int)
    {

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