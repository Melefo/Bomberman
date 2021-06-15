/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AIMapsGenerator
*/

#include "AIMapsGenerator.hpp"

AIMapsGenerator::AIMapsGenerator(std::vector<std::string>& boxmap) : _entities(ECS::Coordinator::GetInstance()->GetEntities()),
_boxmap(InitMaps(boxmap)), _playersmap(InitMaps(boxmap)), 
_bombmap(InitMaps(boxmap))
{
    UpdateMaps();
}


void AIMapsGenerator::Update(double, ECS::Entity&)
{
    RemoveCharsFromMap(_boxmap, {BoxMapValues::BOX});
    RemoveCharsFromMap(_playersmap, {PlayerMapValues::PLAYER});
    RemoveCharsFromMap(_bombmap, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    UpdateMaps();
}

void AIMapsGenerator::UpdateMaps()
{
    std::cout << "Yolo" << std::endl;
    for (auto incr = _entities.begin(); incr != _entities.end();) {
        auto &entity = *incr->get();
        incr++;
        if (!entity.HasComponent<Component::Transform>())
            continue;
        if (entity.GetTag() == "Box") {
            Component::Transform &pos = entity.GetComponent<Component::Transform>();
            _boxmap[static_cast<int>(pos.position.z / 10)][static_cast<int>(pos.position.x / 10)] = BoxMapValues::BOX;
        }
        if (entity.GetTag() == "Player") {
            Component::Transform &pos = entity.GetComponent<Component::Transform>();
            _playersmap[static_cast<int>(pos.position.z / 10)][static_cast<int>(pos.position.x / 10)] = PlayerMapValues::PLAYER;
        }
        if (entity.GetTag() == "Bomb") {
            if (!entity.HasComponent<Component::Explosion>())
                continue;
            Component::Transform &pos = entity.GetComponent<Component::Transform>();
            Component::Explosion &explo = entity.GetComponent<Component::Explosion>();
            _bombmap[static_cast<int>(pos.position.z / 10)][static_cast<int>(pos.position.x / 10)] = static_cast<int>(explo.GetExplosionTimer());
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
                map[i].emplace_back(BoxMapValues::OFFWALL);
            else if (boxmap[i][x] == 'o')
                map[i].emplace_back(BoxMapValues::INWALL);
            else
                map[i].emplace_back(BoxMapValues::EMPTY);
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

const std::vector<std::vector<int>>& AIMapsGenerator::GetBombMap() const
{
    return (_bombmap);
}