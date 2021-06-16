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
             * @brief 
             * 
             * @param dt 
             * @param entity 
             */
            void LateUpdate(double dt, ECS::Entity& entity) override;
            /**
             * @brief 
             * 
             * @param entity 
             */
            std::ostream &operator<<(std::ostream &os) override;
            /**
             * @brief 
             * 
             * @param is 
             * @return std::istream& 
             */
            std::istream &operator>>(std::istream &is) override;
            /**
             * @brief 
             * 
             * @param ptree 
             * @return boost::property_tree::ptree& 
             */
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override;

            RayLib::Vector2<int> GetClosestSymbolPos(RayLib::Vector2<int> agentPos, const std::vector<std::vector<int>>& map, int symbol);

            RayLib::Vector2<int> GetAgentPos(void);

            void GetDirectionsList(RayLib::Vector2<int> aiPos, RayLib::Vector2<int> targetPos, const std::vector<RayLib::Vector2<int>>& map);

            void DebugPath(RayLib::Vector3 startPos);
            void DebugPath(std::vector<RayLib::Vector2<int>> path);

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
            float _speed;
            RayLib::Vector3 _direction;
            std::unique_ptr<RayLib::Window>& _window;

            std::vector<RayLib::Vector3> _directionPath;

            ::AIState _currentState;

            bool _enabled;
            float _stateDuration;
            float _timeToStateChange;

    };
}

#endif /* !AIALGO_HPP_ */