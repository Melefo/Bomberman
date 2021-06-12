/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** GameConfiguration
*/

#ifndef GAMECONFIGURATION_HPP_
#define GAMECONFIGURATION_HPP_

#include "Input.hpp"
#include <vector>
#include <map>
#include "Exceptions.hpp"
#include "EngineExceptions.hpp"

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

        protected:
        private:
            static int _players;
            static int _enemies;

            static std::map<int, playerkeys> _playerKeys;
    };
}

#endif /* !GAMECONFIGURATION_HPP_ */
