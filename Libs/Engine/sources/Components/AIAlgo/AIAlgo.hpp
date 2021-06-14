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

namespace Component
{
    class AIAlgo : public IBehaviour {
        public:
            /**
             * @brief Construct a new AIAlgo object
             * 
             * @param player 
             * @param aimapgen 
             * @param moveSpeed 
             */
            AIAlgo(ECS::Entity &player, AIMapsGenerator& aimapgen, float moveSpeed);
            /**
             * @brief Destroy the AIAlgo object
             * 
             */
            ~AIAlgo() = default;

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
            void SlipperyCollisions(Component::Transform &comp_pos);
            /**
             * @brief 
             * 
             * @param colliders 
             * @param position 
             * @return true 
             * @return false 
             */
            bool CheckCollidersPos(std::vector<std::reference_wrapper<Collider>> colliders, RayLib::Vector3 position);
            /**
             * @brief 
             * 
             * @param os 
             * @return std::ostream& 
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
             * @brief a map who contain the box informations
             * 
             */
            const std::vector<std::vector<int>>& _boxmap;
            /**
             * @brief a map who contain the players informations
             * 
             */
            const std::vector<std::vector<int>>& _playersmap;
            /**
             * @brief a map who contain the bomb power informations
             * 
             */
            const std::vector<std::vector<int>>& _bombpowmap;
            /**
             * @brief a map who contain the bomb timer informations
             * 
             */
            const std::vector<std::vector<int>>& _bombtimermap;
            bool _colliding;
            float _speed;
            RayLib::Vector3 _direction;
            std::unique_ptr<RayLib::Window>& _window;
            float _explotimer;
            AIMapsGenerator& _maps;
    };
}

#endif /* !AIALGO_HPP_ */