/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AIAlgo
*/

#include "AIAlgo.hpp"

namespace Component
{
    AIAlgo::AIAlgo(ECS::Entity &player, AIMapsGenerator& aimapgen, float moveSpeed, float dropDelay) : AController(player, moveSpeed, dropDelay), _ai_player(player), _state(),
    _entities(ECS::Coordinator::GetInstance()->GetEntities()), _boxmap(aimapgen.GetBoxMap()), _playersmap(aimapgen.GetPlayersMap()),
    _bombpowmap(aimapgen.GetBombPowMap()), _bombtimermap(aimapgen.GetBombTimeMap()), _colliding(false), _speed(moveSpeed), _direction(),
    _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype")), _explotimer(), _currentState(AIState::IDLE)
    {
        _state.RunScript("../Libs/Engine/sources/Components/AIAlgo/AIAlgo.lua");
    }

    void AIAlgo::Update(double dt, ECS::Entity& entity)
    {
        if (!_ai_player.HasComponent<Component::Transform>() && !_ai_player.HasComponent<Component::DropBomb>())
            return;
        Component::Transform &comp_pos = _ai_player.GetComponent<Component::Transform>();
        std::vector<int> p_pos = {0, 0, 0};
        //RayLib::Vector3 p_pos;
        int bloc_s = 10;

        p_pos[0] = (int) comp_pos.position.x / bloc_s;
        p_pos[2] = (int) comp_pos.position.z / bloc_s;
        if (_state.Call<bool>("is_safe", p_pos, _bombtimermap) == true) {
            if (_state.Call<bool>("is_close_to_box", p_pos, _boxmap, _bombtimermap) && _explotimer <= 0) {
                _dropBomb.InstantiateBomb(comp_pos.position, Explosion::ExplosionType::CIRCLE);
                _explotimer = 3;
                //std::cout << "go there" << std::endl;
            }
            _state.Call<int>("get_safe_direction", p_pos, _boxmap, _bombtimermap);
        } else {
            _state.Call<int>("get_safe_direction", p_pos, _boxmap, _bombtimermap);
        }
        _direction.x = _state.GetGlobal<float>("Xdir");
        _direction.z = _state.GetGlobal<float>("Zdir");
        if (_explotimer > 0)
            _explotimer -= _window->GetFrameTime();

        _movement.direction = _direction;

        _movement.Update(dt, entity);
        _dropBomb.Update();
    }

    void AIAlgo::FixedUpdate(ECS::Entity& entity)
    {
        _movement.FixedUpdate(entity);
    }

    void AIAlgo::LateUpdate(double, ECS::Entity&)
    {

    }

    void AIAlgo::GeneratePathToSymbol(RayLib::Vector3, int )
    {
        // vector directions = {up, down, left, right}

        // foreach dir in directions:
            // if map[position + dir] == symbol
                // _directions.push_back(dir)
                // return

            // else if map[position + dir] != box && map[position + dir] != wall (position is free to move to)
                // _directions.push_back(dir)
                // generatePathtoSymbol(position + dir, symbol)
                // break
    }

    std::ostream &AIAlgo::operator<<(std::ostream &os)
    {
        return (os);
    }

    std::istream &AIAlgo::operator>>(std::istream &is)
    {
        return (is);
    }

    boost::property_tree::ptree& AIAlgo::operator<<(boost::property_tree::ptree &ptree)
    {
        return (ptree);
    }
}