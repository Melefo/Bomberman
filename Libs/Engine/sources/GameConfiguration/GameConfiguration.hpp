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

            static playerkeys& GetPlayerKeys(int player);
            static int GetPlayers(void);

            static int GetEnemies(void);
            static void SetEnemies(int total);

            static void SetPlayers(int playersTotal);
            static void SetPlayerKeys(int player, RayLib::Input& input, int actionKey);

            static bool GetDebugMode(void);
            static void SetDebugMode(bool);

            static unsigned int GetSeed(void);
            static void SetSeed(unsigned int);

            static bool GetGameOver(void);
            static void SetGameOver(bool gameOver);

            static TerrainGenerator &GetTerrainGenerator(void);

        protected:
        private:
            static int _players;
            static int _enemies;
            static unsigned int _seed;
            static bool _debugMode;
            static bool _gameOver;
            static TerrainGenerator _terrainGenerator;
            static std::map<int, playerkeys> _playerKeys;
    };
}

#endif /* !GAMECONFIGURATION_HPP_ */
