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

enum MapSymbols
{
    PLAYER,
    BOX_HP_1,
    BOX_HP_2,
    BOX_HP_3,
    WALL,
    BOMB,
    EMPTY
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
        const std::vector<std::vector<int>>& GetBombPowMap() const;
        const std::vector<std::vector<int>>& GetBombTimeMap() const;
    protected:
    private:
        const std::list<std::unique_ptr<ECS::Entity>>& _entities;
        std::vector<std::vector<int>> _boxmap;
        std::vector<std::vector<int>> _playersmap;
        std::vector<std::vector<int>> _bombpowmap;
        std::vector<std::vector<int>> _bombtimermap;
};

#endif /* !AIMAPSGENERATOR_HPP_ */
