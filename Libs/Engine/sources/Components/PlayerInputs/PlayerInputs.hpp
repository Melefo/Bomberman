/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PlayerInputs
*/

#ifndef PLAYERINPUTS_HPP_
#define PLAYERINPUTS_HPP_

#include "IBehaviour.hpp"
#include "Input.hpp"
#include "Movement.hpp"
#include "DropBomb.hpp"
#include "AController.hpp"

namespace Component
{
    class PlayerInputs : public AController {
        public:
            /**
             * @brief Construct a new Player Inputs object
             * 
             * @param attatchedEntity 
             * @param input 
             * @param dropBombKey 
             * @param speed 
             * @param dropDelay 
             */
            PlayerInputs(ECS::Entity& attatchedEntity, RayLib::Input input=RayLib::Input(), int dropBombKey=KEY_X, float speed=0.5f, float dropDelay=2.5f);
            /**
             * @brief Destroy the Player Inputs object
             * 
             */
            ~PlayerInputs() override = default;
            /**
             * @brief Construct a new Player Inputs object
             * 
             * @param other 
             */
            PlayerInputs(const PlayerInputs& other) = default;
            /**
             * @brief Assignement operator
             * 
             * @param other 
             * @return PlayerInputs& 
             */
            PlayerInputs& operator=(const PlayerInputs& other) = default;

            /**
             * @brief Used to sample the input
             * 
             * @param dt 
             */
            void Update(double dt, ECS::Entity& entity) override;

            /**
             * @brief Used to modify the velocity regularly
             * 
             * @param entity 
             */
            void FixedUpdate(ECS::Entity&) override;
            /**
             * @brief 
             * 
             * @param dt 
             * @param entity 
             */
            void LateUpdate(double, ECS::Entity&) override;

            std::ostream &operator<<(std::ostream &os) override {return os;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

        protected:
        private:
            /**
             * @brief Input class to check the keypress
             * 
             */
            RayLib::Input _input;
            std::unique_ptr<RayLib::Window>& _window;
            /**
             * @brief Bomb drop input key
             * 
             */
            int _bombKey;
            /**
             * @brief Attatched entity
             * 
             */
            ECS::Entity& _entity;
    };
}

#endif /* !PLAYERINPUTS_HPP_ */
