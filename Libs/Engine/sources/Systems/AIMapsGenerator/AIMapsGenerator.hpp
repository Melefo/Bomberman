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


enum BoxMapValues {
    OFFWALL = -21,
    INWALL = -20,
    EMPTY = -3,
    BOX = 1
};

enum BombMapValues {
    EMPTY = -3,
    BOMB = 0
};

enum PlayerMapValues {
    PLAYER = 1,
    EMPTY = -3
};

class AIMapsGenerator : public ECS::ASystem {
    public:
        AIMapsGenerator(std::vector<std::string>& boxmap);
        ~AIMapsGenerator() = default;;

        void Update(double dt, ECS::Entity& entity) override;
        void FixedUpdate(ECS::Entity& entity) override;
        void LateUpdate(double dt, ECS::Entity& entity) override;
        void UpdateMaps();
        std::vector<std::vector<int>> InitMaps(std::vector<std::string>& boxmap);
        std::vector<std::vector<int>>& RemoveCharsFromMap(std::vector<std::vector<int>>& map, std::vector<int> chars);
        const std::vector<std::vector<int>>& GetBoxMap() const;
        const std::vector<std::vector<int>>& GetPlayersMap() const;
        const std::vector<std::vector<int>>& GetBombMap() const;
    protected:
    private:
        const std::list<std::unique_ptr<ECS::Entity>>& _entities;
        std::vector<std::vector<int>> _boxmap;
        std::vector<std::vector<int>> _playersmap;
        std::vector<std::vector<int>> _bombmap;
};

#endif /* !AIMAPSGENERATOR_HPP_ */
