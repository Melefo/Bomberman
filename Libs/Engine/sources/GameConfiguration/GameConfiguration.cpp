/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** GameConfiguration
*/

#include "GameConfiguration.hpp"
#include <iostream>
#include "Coordinator.hpp"
#include "IComponent.hpp"

namespace Engine
{
    RayLib::Vector2<int> GameConfiguration::_mapSize = {15, 15};
    int GameConfiguration::_players = 2;
    int GameConfiguration::_IA = 0;
    bool GameConfiguration::_debugMode = false;
    bool GameConfiguration::_isMapBasic = true;
    unsigned int GameConfiguration::_seed = 0;
    bool GameConfiguration::_gameOver = false;
    std::map<int, playerkeys> GameConfiguration::_playerKeys = {};
    TerrainGenerator GameConfiguration::_terrainGenerator = TerrainGenerator(Engine::GameConfiguration::GetPlayers() + Engine::GameConfiguration::GetIA(),
                                                                             Engine::GameConfiguration::GetMapSize().x, Engine::GameConfiguration::GetMapSize().y);
    bool GameConfiguration::_droppedMap = false;

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

    int GameConfiguration::GetIA(void)
    {
        return (_IA);
    }

    void GameConfiguration::SetIA(int total)
    {
        _IA = total;
    }

    bool GameConfiguration::GetDebugMode(void)
    {
        return (_debugMode);
    }

    void GameConfiguration::SetDebugMode(bool mode)
    {
        _debugMode = mode;
    }

    unsigned int GameConfiguration::GetSeed(void)
    {
        return (_seed);
    }

    void GameConfiguration::SetSeed(unsigned int seed)
    {
        _seed = seed;
    }

    bool GameConfiguration::GetGameOver(void)
    {
        return (_gameOver);
    }

    void GameConfiguration::SetGameOver(bool gameOver)
    {
        _gameOver = gameOver;
    }

    RayLib::Vector2<int> GameConfiguration::GetMapSize(void)
    {
        return _mapSize;
    }

    void GameConfiguration::SetMapSize(int x, int y)
    {
        _mapSize.x = x;
        _mapSize.y = y;
    }

    TerrainGenerator &GameConfiguration::GetTerrainGenerator(void)
    {
        return (_terrainGenerator);
    }

    bool GameConfiguration::GetIsMapBasic(void)
    {
        return (_isMapBasic);
    }

    void GameConfiguration::SetIsMapBasic(bool value)
    {
        _isMapBasic = value;
    }

    void GameConfiguration::SetDroppedMap(bool isDropped)
    {
        _droppedMap = isDropped;
    }

    bool GameConfiguration::GetDroppedMap(void)
    {
        return (_droppedMap);
    }

    void GameConfiguration::SaveMap(void)
    {
        // open a file called map.xml
        std::ofstream file("./map.xml", std::ofstream::trunc | std::ofstream::out);

        // get coordinator
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        // get entities
        const std::list<std::unique_ptr<ECS::Entity>>& entities = coordinator->GetEntities();
        std::ostringstream oss;

        for (auto it = entities.begin(); it != entities.end(); it++) {
            if (it->get()->GetTag() != "Wall" && it->get()->GetTag() != "Box")
                continue;
            std::vector<std::reference_wrapper<std::unique_ptr<ECS::IComponent>>> components = it->get()->GetComponents();
            oss << "<Entity>";

            oss << "<tag>" << it->get()->GetTag() << "</tag>";
            for (auto cmp = components.begin(); cmp != components.end(); cmp++) {
                IXMLSerializable& obj = *cmp->get();
                oss << obj;
            }
            oss << "</Entity>";
        }
        file << "<Entities>";
        file << oss.str();
        file << "</Entities>";
        file.close();
    }

    void GameConfiguration::SaveMap(const std::string& terrainPath)
    {
        if (!_terrainGenerator.isGenerated())
            return;
        std::ofstream file(terrainPath + ".txt", std::ofstream::trunc | std::ofstream::out);
        std::ostringstream oss;

        const std::vector<std::string> terrain = _terrainGenerator.getMap();

        for (auto line : terrain) {
            oss << line << std::endl;
        }
        file << oss.str();
        file.close();
    }

}
