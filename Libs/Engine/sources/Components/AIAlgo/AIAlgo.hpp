/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** AIAlgo
*/

/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AIAlgo
*/

#ifndef AIALGO_HPP_
#define AIALGO_HPP_

#include "IComponent.hpp"
#include <cinttypes>
#include <iostream>
#include "Vector3.hpp"
#include "IBehaviour.hpp"
#include "Window.hpp"
#include "CollisionSystem.hpp"
#include "Transform.hpp"
#include "Destructible.hpp"
#include "Exceptions.hpp"
#include "Explosion.hpp"
#include "PhysicsBody.hpp"
#include "Collider.hpp"
#include "DropBomb.hpp"
#include "State.hpp"
#include "AIMapsGenerator.hpp"
#include "Movement.hpp"
#include "AController.hpp"
#include "GameConfiguration.hpp"

enum class AIState
{
    IDLE,
    CHASE,
    HIDE,
    ATTACK
};

namespace Component
{
    class AIAlgo : public AController {
        public:
            /**
             * @brief Construct a new AIAlgo object
             * 
             * @param player 
             * @param aimapgen 
             * @param moveSpeed 
             */
            AIAlgo(ECS::Entity &player, float moveSpeed, float dropDelay=2.5f);
            /**
             * @brief Destroy the AIAlgo object
             * 
             */
            ~AIAlgo() override = default;

            /**
             * @brief Copy a new AIAlgo object
             *
             */
            AIAlgo(const AIAlgo&) = default;

            /**
             * @brief Assign a new AIAlgo object
             *
             * @return AIAlgo& assigned AIAlgo
             */
            AIAlgo& operator=(const AIAlgo&) = default;

            /**
             * @brief Updates the ai algorithm
             * 
             * @param dt 
             * @param entity 
             */
            void Update(double dt, ECS::Entity& entity) override;
            /**
             * @brief Fixed Update
             * 
             * @param entity 
             */
            void FixedUpdate(ECS::Entity& entity) override;
            /**
             * @brief LateUpdate
             * 
             * @param dt 
             * @param entity 
             */
            void LateUpdate(double dt, ECS::Entity& entity) override;
            /**
             * @brief Send AIAlgo to a stream
             * 
             * @param entity 
             */
            std::ostream &operator<<(std::ostream &os) override;
            /**
             * @brief Send AIAlgo to a Boost ptree
             * 
             * @param ptree 
             * @return boost::property_tree::ptree& 
             */
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override;

            /**
             * @brief Get the Closest Symbol Pos object
             * 
             * @param agentPos 
             * @param map 
             * @param symbol 
             * @return RayLib::Vector2<int> 
             */
            RayLib::Vector2<int> GetClosestSymbolPos(RayLib::Vector2<int> agentPos, const std::vector<std::vector<int>>& map, int symbol);
            /**
             * @brief Get the Best Safe Pos object
             * 
             * @param agentPos 
             * @param map 
             * @param mapPositions 
             * @return RayLib::Vector2<int> 
             */
            RayLib::Vector2<int> GetBestSafePos(RayLib::Vector2<int> agentPos, const std::vector<std::vector<int>>& map, const std::vector<RayLib::Vector2<int>>& mapPositions);
            /**
             * @brief Get the Best Box Pos object
             * 
             * @param agentPos 
             * @param map 
             * @param mapPositions 
             * @return RayLib::Vector2<int> 
             */
            RayLib::Vector2<int> GetBestBoxPos(RayLib::Vector2<int> agentPos, const std::vector<std::vector<int>>& map, const std::vector<RayLib::Vector2<int>>& mapPositions);
            /**
             * @brief Get the Best Pos object
             * 
             * @param agentPos 
             * @param map 
             * @param mapPositions 
             * @param value 
             * @return RayLib::Vector2<int> 
             */
            RayLib::Vector2<int> GetBestPos(RayLib::Vector2<int> agentPos, const std::vector<std::vector<int>>& map, const std::vector<RayLib::Vector2<int>>& mapPositions, int value);

            /**
             * @brief Get the Agent Pos object
             * 
             * @return RayLib::Vector2<int> 
             */
            RayLib::Vector2<int> GetAgentPos(void);

            /**
             * @brief Get the Directions List object
             * 
             * @param aiPos 
             * @param targetPos 
             * @param mapPositions 
             * @param map 
             */
            void GetDirectionsList(RayLib::Vector2<int> aiPos, RayLib::Vector2<int> targetPos, const std::vector<RayLib::Vector2<int>>& mapPositions, const std::vector<std::vector<int>>& map);

            /**
             * @brief Print the path generated
             * 
             * @param startPos 
             */
            void DebugPath(RayLib::Vector3 startPos);
            /**
             * @brief Print a path to a target
             * 
             * @param path 
             * @param targetPos 
             */
            void DebugPath(std::vector<RayLib::Vector2<int>> path, RayLib::Vector2<int> targetPos);

            /**
             * @brief Get the Map As Positions object
             * 
             * @param map 
             * @return std::vector<RayLib::Vector2<int>> 
             */
            std::vector<RayLib::Vector2<int>> GetMapAsPositions(const std::vector<std::vector<int>>& map);


        protected:
        private:
            /**
             * @brief refence to self in order to dispose after exploding
             * 
             */
            ECS::Entity &_ai_player;
            /**
             * @brief Lua state
             * 
             */
            Lua::State _state;
            /**
             * @brief list of all entities
             * 
             */
            const std::list<std::unique_ptr<ECS::Entity>>& _entities;
            /**
             * @brief Speed of the AI
             * 
             */
            float _speed;
            /**
             * @brief Direction of the AI
             * 
             */
            RayLib::Vector3 _direction;
            /**
             * @brief Pointer to the current window
             * 
             */
            std::unique_ptr<RayLib::Window>& _window;

            /**
             * @brief List of direction to a target
             * 
             */
            std::vector<RayLib::Vector3> _directionPath;

            /**
             * @brief Current State of the AI
             * 
             */
            ::AIState _currentState;

            /**
             * @brief Is the IA enabled
             * 
             */
            bool _enabled;
            /**
             * @brief Duration of the current state
             * 
             */
            float _stateDuration;
            /**
             * @brief Duration needed before switching state
             * 
             */
            float _timeToStateChange;

    };
}

#endif /* !AIALGO_HPP_ */