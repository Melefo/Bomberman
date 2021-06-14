/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AIMapsGenerator
*/

#include "AIMapsGenerator.hpp"

AIMapsGenerator::AIMapsGenerator(std::vector<std::string>& boxmap) : _entities(ECS::Coordinator::GetInstance()->GetEntities()),
_boxmap(InitMaps(boxmap)), _playersmap(InitMaps(boxmap)), 
_bombpowmap(InitMaps(boxmap)), _bombtimermap(InitMaps(boxmap))
{
}


void AIMapsGenerator::Update(double, ECS::Entity&)
{
    RemoveCharsFromMap(_boxmap, {1, 2, 3});
    RemoveCharsFromMap(_playersmap, {1, 2, 3});
    RemoveCharsFromMap(_bombpowmap, {1, 2, 3});
    RemoveCharsFromMap(_bombtimermap, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    UpdateMaps();
}

void AIMapsGenerator::UpdateMaps()
{
    for (auto incr = _entities.begin(); incr != _entities.end();) {
        auto &entity = *incr->get();
        incr++;
        if (entity.GetTag() == "Box") {
            Component::Transform &pos = entity.GetComponent<Component::Transform>();
            Component::Destructible &dura = entity.GetComponent<Component::Destructible>();
            if (dura.GetResistance() == 1) {
                _boxmap[static_cast<int>(pos.position.z / 10)][static_cast<int>(pos.position.x / 10)] = 1;
            } else if (dura.GetResistance() == 2) {
                _boxmap[static_cast<int>(pos.position.z / 10)][static_cast<int>(pos.position.x / 10)] = 2;
            } else {
                _boxmap[static_cast<int>(pos.position.z / 10)][static_cast<int>(pos.position.x / 10)] = 3;
            }
        }
        if (entity.GetTag() == "Player") {
            Component::Transform &pos = entity.GetComponent<Component::Transform>();
            _playersmap[static_cast<int>(pos.position.z / 10)][static_cast<int>(pos.position.x / 10)] = 1;
        }
        if (entity.GetTag() == "Bomb") {
            Component::Transform &pos = entity.GetComponent<Component::Transform>();
            Component::Explosion &explo = entity.GetComponent<Component::Explosion>();
            _bombpowmap[static_cast<int>(pos.position.z / 10)][static_cast<int>(pos.position.x / 10)] = explo.power;
            _bombtimermap[static_cast<int>(pos.position.z / 10)][static_cast<int>(pos.position.x / 10)] = static_cast<int>(explo.GetExplosionTimer());
        }
    }
}

void AIMapsGenerator::FixedUpdate(ECS::Entity&)
{
}

void AIMapsGenerator::LateUpdate(double, ECS::Entity&)
{

}

std::vector<std::vector<int>> AIMapsGenerator::InitMaps(std::vector<std::string>& boxmap)
{
    std::vector<std::vector<int>> map;

    for (std::size_t i = 0; i < boxmap.size(); i++) {
        map.emplace_back();
        for (std::size_t x = 0; x < boxmap[i].size(); x++) {
            if (boxmap[i][x] == 'X')
                map[i].emplace_back(-20);
            else if (boxmap[i][x] == 'o')
                map[i].emplace_back(-21);
            else
                map[i].emplace_back(-3);
        }
    }
    return (map);
}

std::vector<std::vector<int>>& AIMapsGenerator::RemoveCharsFromMap(std::vector<std::vector<int>>& map, std::vector<int> values)
{
    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t v = 0; v < values.size(); v++) {
            std::replace(map[i].begin(), map[i].end(), values.at(v), -1);
        }
    }
    return (map);
}

const std::vector<std::vector<int>>& AIMapsGenerator::GetBoxMap() const
{
    return (_boxmap);
}

const std::vector<std::vector<int>>& AIMapsGenerator::GetPlayersMap() const
{
    return (_playersmap);
}

const std::vector<std::vector<int>>& AIMapsGenerator::GetBombPowMap() const
{
    return (_bombpowmap);
}

const std::vector<std::vector<int>>& AIMapsGenerator::GetBombTimeMap() const
{
    return (_bombtimermap);
}