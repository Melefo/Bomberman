/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** GameConfiguration
*/

#ifndef GAMECONFIGURATION_HPP_
#define GAMECONFIGURATION_HPP_

#include "Input.hpp"
#include "Exceptions.hpp"
#include "EngineExceptions.hpp"
#include "Vector2.hpp"
#include "TerrainGenerator.hpp"
#include <vector>
#include <map>

namespace Engine
{
    struct playerkeys
    {
        playerkeys(RayLib::Input input = RayLib::Input(), int key = KEY_X);
        RayLib::Input movementInput;
        int actionKey;
    };

    class GameConfiguration {
        public:
            /**
             * @brief Construct a new Game Configuration object
             * 
             */
            GameConfiguration() = default;
            /**
             * @brief Destroy the Game Configuration object
             * 
             */
            ~GameConfiguration()= default;

            /**
             * @brief Get the Player Keys object
             * 
             * @param int player 
             * @return playerkeys& playerkeys 
             */
            static playerkeys& GetPlayerKeys(int player);
            /**
             * @brief Get the nbr of players
             * 
             * @return int 
             */
            static int GetPlayers(void);

            /**
             * @brief Get the nbr of IAs
             * 
             * @return int 
             */
            static int GetIA(void);
            /**
             * @brief Set the nbr of IAs
             * 
             * @param int total 
             */
            static void SetIA(int total);

            /**
             * @brief Set the nbr of players
             * 
             * @param int playersTotal 
             */
            static void SetPlayers(int playersTotal);
            /**
             * @brief Set the Player Keys for the player nbr given
             * 
             * @param int player 
             * @param RayLib::Input& input 
             * @param int actionKey 
             */
            static void SetPlayerKeys(int player, RayLib::Input& input, int actionKey);

            /**
             * @brief Get the size of the map
             * 
             * @return RayLib::Vector2<int> 
             */
            static RayLib::Vector2<int> GetMapSize(void);
            /**
             * @brief Set the size of the map
             * 
             * @param int x 
             * @param int y 
             */
            static void SetMapSize(int x, int y);

            /**
             * @brief Is the map basic ?
             * 
             * @return true 
             * @return false 
             */
            static bool GetIsMapBasic(void);
            /**
             * @brief Set if the map is basic or not
             * 
             * @param bool value 
             */
            static void SetIsMapBasic(bool value);

            /**
             * @brief Is the mode debug enabled
             * 
             * @return true 
             * @return false 
             */
            static bool GetDebugMode(void);
            /**
             * @brief Set the mode to debug
             * 
             * @param bool mode
             */
            static void SetDebugMode(bool mode);

            /**
             * @brief Get the seed
             * 
             * @return unsigned int 
             */
            static unsigned int GetSeed(void);
            /**
             * @brief Set the seed
             * 
             * @param unsigned int seed 
             */
            static void SetSeed(unsigned int seed);

            /**
             * @brief Is the Game over
             * 
             * @return true 
             * @return false 
             */
            static bool GetGameOver(void);
            /**
             * @brief Set the the game over
             * 
             * @param bool gameOver 
             */
            static void SetGameOver(bool gameOver);

            /**
             * @brief Save the current map in .xml
             * 
             */
            static void SaveMap(void);
            /**
             * @brief Save the current map with at the filepath
             * 
             * @param const std::string& path 
             */
            static void SaveMap(const std::string& path);

            /**
             * @brief Set the _droppedMap
             * 
             * @param bool isDropped 
             */
            static void SetDroppedMap(bool isDropped);
            /**
             * @brief Get the _droppedMap
             * 
             * @return true 
             * @return false 
             */
            static bool GetDroppedMap(void);

            /**
             * @brief Set the volume
             * 
             * @param float volume 
             */
            static void SetVolume(float volume);
            /**
             * @brief Get the volume 
             * 
             * @return float 
             */
            static float GetVolume(void);

            static TerrainGenerator &GetTerrainGenerator(void);

        protected:
        private:
            static RayLib::Vector2<int> _mapSize;
            static int _players;
            static int _IA;
            static unsigned int _seed;
            static bool _debugMode;
            static bool _isMapBasic;
            static bool _gameOver;
            static TerrainGenerator _terrainGenerator;
            static std::map<int, playerkeys> _playerKeys;
            static bool _droppedMap;
            static float _volume;
    };
}

#endif /* !GAMECONFIGURATION_HPP_ */
