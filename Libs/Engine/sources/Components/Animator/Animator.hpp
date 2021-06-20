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
#include "AssetCache.hpp"
#include "Entity.hpp"
#include <map>
#include <memory>

namespace Component
{

    class Animator : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Animator object
             * @param assetName
             * @param stateName 
             */
            Animator(ECS::Entity& entity, const std::string& path, std::string stateName);
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
             * @brief Set the current State
             * 
             * @param state 
             */
            void SetState(const std::string& state);

            /**
             * @brief Add a state
             * 
             * @param path 
             * @param state 
             */
            void AddState(const std::string& path, std::string state);

            /**
             * @brief Get the State object
             * 
             * @return const std::string& 
             */
            const std::string& GetState(void) const;

            /**
             * @brief Play animation at current state of statemachine
             * 
             * @param model 
             */
            void PlayCurrentState(RayLib::Model& model);

            std::ostream &operator<<(std::ostream &os) override {return os;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

        protected:
        private:
            /**
             * @brief List of states
             * 
             */
            std::map<std::string, std::shared_ptr<RayLib::ModelAnimation>> _stateMachine;
            /**
             * @brief current State of animation
             * 
             */
            std::string _currentState;
            /**
             * @brief Assoiciated animation
             * 
             */
            ECS::Entity& _entity;
    };
}

#endif /* !ANIMATOR_HPP_ */
