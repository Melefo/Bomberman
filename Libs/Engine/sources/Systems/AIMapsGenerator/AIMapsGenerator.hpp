/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AIMapsGenerator
*/

#ifndef AIMAPSGENERATOR_HPP_
#define AIMAPSGENERATOR_HPP_

#include "IComponent.hpp"
#include "ASystem.hpp"
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
#include "GameConfigurator.hpp"
#include "Camera.hpp"

enum BoxMapValues {
    OFFWALL = -21,
    INWALL = -20,
    BOX = -1,
    EMPTY = -3
};

enum BombMapValues {
    BOMB = 0
};

enum PlayerMapValues {
    PLAYER = 1
};

class AIMapsGenerator : public ECS::ASystem {
    public:
        /**
         * @brief Construct a new AIMapsGenerator object
         * 
         * @param boxmap 
         */
        AIMapsGenerator(std::vector<std::string>& boxmap);
        /**
         * @brief Destroy the AIMapsGenerator object
         * 
         */
        ~AIMapsGenerator() = default;
        /**
         * @brief Construct a new AIMapsGenerator object
         * 
         * @param other 
         */
        AIMapsGenerator(const AIMapsGenerator& other) = default;
        /**
         * @brief Assignement operator
         * 
         * @param other 
         * @return AIMapsGenerator& 
         */
        AIMapsGenerator& operator=(const AIMapsGenerator& other) = default;

        /**
         * @brief Update an entity
         * 
         * @param dt 
         * @param entity 
         */
        void Update(double dt, ECS::Entity& entity) override;
        /**
         * @brief Update an entity at a fixed time
         * 
         * @param entity 
         */
        void FixedUpdate(ECS::Entity& entity) override;
        /**
         * @brief Update an entity after the others
         * 
         * @param dt 
         * @param entity 
         */
        void LateUpdate(double dt, ECS::Entity& entity) override;
        /**
         * @brief Update AI maps
         * 
         * @param entity 
         */
        void UpdateMaps(ECS::Entity& entity);
        /**
         * @brief Initialize AI maps
         * 
         * @param entity 
         */
        void InitMaps(ECS::Entity& entity);
        /**
         * @brief Initialize all maps from a another map type
         * 
         * @param boxmap 
         * @return std::vector<std::vector<int>> 
         */
        std::vector<std::vector<int>> InitMaps(std::vector<std::string>& boxmap);
        /**
         * @brief remove unwanted char from the map
         * 
         * @param map 
         * @param chars 
         * @return std::vector<std::vector<int>>& 
         */
        std::vector<std::vector<int>>& RemoveCharsFromMap(std::vector<std::vector<int>>& map, std::vector<int> chars);
        /**
         * @brief Get the Box Map object
         * 
         * @return const std::vector<std::vector<int>>& 
         */
        const std::vector<std::vector<int>>& GetBoxMap() const;
        /**
         * @brief Get the Players Map object
         * 
         * @return const std::vector<std::vector<int>>& 
         */
        const std::vector<std::vector<int>>& GetPlayersMap() const;
    protected:
    private:
        std::vector<std::vector<int>> _boxmap;
        std::vector<std::vector<int>> _playersmap;
        std::vector<std::string> _stringMap;
};

#endif /* !AIMAPSGENERATOR_HPP_ */
