/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** GameConfigurator
*/

#ifndef GAMECONFIGURATOR_HPP_
#define GAMECONFIGURATOR_HPP_

#include "IBehaviour.hpp"
#include "Window.hpp"
#include "EntityLoader.hpp"
#include "GameConfiguration.hpp"

namespace Component
{
    class GameConfigurator : public IBehaviour {
        public:
            GameConfigurator();
            ~GameConfigurator() override = default;

            /**
             * @brief Called once per cpu update
             * 
             * @param dt Time since last call to update
             */
            void Update(double dt, ECS::Entity& entity) override;
            /**
             * @brief Called every fixed seconds (CF coordinator)
             * 
             * @param entity 
             */
            void FixedUpdate(ECS::Entity& entity) override;

            /**
             * @brief Late update
             * 
             * @param dt 
             * @param entity 
             */
            void LateUpdate(double dt, ECS::Entity& entity) override;

            /**
             * @brief Remove old entities, and parse the file into entities
             * 
             * @param path 
             */
            void ParseXMLEntities(const std::string& path);
            /**
             * @brief Remove old entities, use the map given to create entities
             * 
             * @param path 
             */
            void ParseTerrain(const std::string& path);

            /**
             * @brief Checks if the game is over
             * 
             * @return true 
             * @return false 
             */
            bool CheckGameOver(void);

            /**
             * @brief Reset all PlayerEntyties animation to "Idle"
             * 
             */
            void ResetPlayersAnimations();

            std::ostream &operator<<(std::ostream &os) override {return os;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};


        protected:
        private:
            std::unique_ptr<RayLib::Window>& _window;
            std::unique_ptr<ECS::Coordinator>& _coordinator;

            int _nbrPlayersAlive;
            int _nbrIAsAlive;
    };
}

#endif /* !GAMECONFIGURATOR_HPP_ */
