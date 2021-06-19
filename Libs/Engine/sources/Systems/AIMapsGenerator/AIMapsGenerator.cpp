/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AIMapsGenerator
*/

#include "AIMapsGenerator.hpp"

AIMapsGenerator::AIMapsGenerator(std::vector<std::string>& boxmap) :
_boxmap(InitMaps(boxmap)), _playersmap(InitMaps(boxmap)), _stringMap(boxmap)
{
    this->AddDependency<Component::Camera>();
    for (auto& entity : ECS::Coordinator::GetInstance()->GetEntities())
        InitMaps(*entity);
}

void AIMapsGenerator::Update(double, ECS::Entity&)
{
    RemoveCharsFromMap(_playersmap, {PlayerMapValues::PLAYER});
    RemoveCharsFromMap(_boxmap, {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

    for (auto& entity : ECS::Coordinator::GetInstance()->GetEntities()) {
        InitMaps(*entity);
    }
}

void AIMapsGenerator::UpdateMaps(ECS::Entity& entity)
{
    if (entity.GetTag() == "Player" || entity.GetTag() == "AI") {
        Component::Transform& pos = entity.GetComponent<Component::Transform>();
        _playersmap[static_cast<int>(pos.position.z / 10)][static_cast<int>(pos.position.x / 10)] = PlayerMapValues::PLAYER;
    }
    if (entity.GetTag() == "Bomb") {
        if (!entity.HasComponent<Component::Explosion>())
            return;
        Component::Transform& pos = entity.GetComponent<Component::Transform>();
        Component::Explosion &explo = entity.GetComponent<Component::Explosion>();
        if (_boxmap[static_cast<int>(round(pos.position.z / 10))][static_cast<int>(round(pos.position.x / 10))] == BoxMapValues::BOX)
            return;
        _boxmap[static_cast<int>(round(pos.position.z / 10))][static_cast<int>(round(pos.position.x / 10))] = static_cast<int>(explo.GetExplosionTimer());
    }
}

void AIMapsGenerator::InitMaps(ECS::Entity& entity)
{
    this->UpdateMaps(entity);
    if (entity.GetTag() == "Box")
    {
        Component::Transform& pos = entity.GetComponent<Component::Transform>();
        _boxmap[static_cast<int>(pos.position.z / 10)][static_cast<int>(pos.position.x / 10)] = BoxMapValues::BOX;
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
            std::replace(map[i].begin(), map[i].end(), values.at(v), static_cast<int>(BoxMapValues::EMPTY));
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