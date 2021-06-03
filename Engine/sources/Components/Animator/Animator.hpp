/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Animator
*/

#ifndef ANIMATOR_HPP_
#define ANIMATOR_HPP_

#include "IComponent.hpp"
#include "ModelAnimation.hpp"
#include <map>

namespace Component
{

    class Animator : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Animator object
             * Initialize a state with a modelanimation and a statename
             * @param filePath 
             * @param stateName 
             */
            Animator(const std::string& filePath, std::string stateName);
            /**
             * @brief Destroy the Animator object
             * 
             */
            ~Animator() = default;
            /**
             * @brief Construct a new Animator object
             * 
             * @param other 
             */
            Animator(const Animator& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return Animator& 
             */
            Animator& operator=(const Animator& other) = default;

            /**
             * @brief Set the State
             * 
             * @param state 
             */
            void SetState(const std::string& state);

            void PlayCurrentState(RayLib::Model& model);
        protected:
        private:
            std::map<std::string, RayLib::ModelAnimation> _stateMachine;
            std::string _currentState;
    };
}

#endif /* !ANIMATOR_HPP_ */
