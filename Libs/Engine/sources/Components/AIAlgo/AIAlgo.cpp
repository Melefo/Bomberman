/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AIAlgo
*/

#include "AIAlgo.hpp"

namespace Component
{
    AIAlgo::AIAlgo(ECS::Entity &player, AIMapsGenerator& aimapgen, float moveSpeed, float dropDelay) : AController(player, moveSpeed, dropDelay),
    _ai_player(player), _state(), _entities(ECS::Coordinator::GetInstance()->GetEntities()), _boxmap(aimapgen.GetBoxMap()),
    _playersmap(aimapgen.GetPlayersMap()), _bombpowmap(aimapgen.GetBombPowMap()), _bombtimermap(aimapgen.GetBombTimeMap()),
    _speed(moveSpeed), _direction(), _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype")),
    _currentState(AIState::IDLE)
    {
        _state.RunScript("../Libs/Engine/sources/Components/AIAlgo/AIAlgo.lua");
    }

    void AIAlgo::Update(double dt, ECS::Entity& entity)
    {
        Component::Transform &transform = _ai_player.GetComponent<Component::Transform>();
        /*if (!_ai_player.HasComponent<Component::Transform>() && !_ai_player.HasComponent<Component::DropBomb>())
            return;
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
            _explotimer -= _window->GetFrameTime();*/


        if (_currentState == AIState::IDLE) {
            _direction = RayLib::Vector3();
        }
        if (_currentState == AIState::HIDE) {
            // _direction = dirToSafety()
        }
        if (_currentState == AIState::CHASE) {
            // _direction = dirToPlayer();
            // if no direct line to player:
                // _direction = dirToBox();
        }
        if (_currentState == AIState::ATTACK) {
            _dropBomb.InstantiateBomb(transform.position);
            _currentState = AIState::HIDE;
        }

        if (Engine::GameConfiguration::GetDebugMode())
            DebugPath(transform.position);

        _movement.direction = _direction;

        _movement.Update(dt, entity);
        _dropBomb.Update();
    }

    void AIAlgo::DebugPath(RayLib::Vector3 startPos)
    {
        RayLib::Vector3 currentPos = startPos;

        _window->DrawCubeWires(currentPos, 5.0f, RED);

        for (auto dir = _directionPath.begin(); dir != _directionPath.end(); dir++) {
            currentPos += *dir;
            _window->DrawCubeWires(currentPos, 5.0f, RED);
        }
    }

    void AIAlgo::FixedUpdate(ECS::Entity& entity)
    {
        _movement.FixedUpdate(entity);
    }

    void AIAlgo::LateUpdate(double, ECS::Entity&)
    {

    }

    std::vector<RayLib::Vector3> AIAlgo::GeneratePathToSymbol(RayLib::Vector3 position, int symbol)
    {
        std::vector<RayLib::Vector3> directions = {RayLib::Vector3(0.0f, 0.0f, 1.0f),
                                                   RayLib::Vector3(0.0f, 0.0f, -1.0f),
                                                   RayLib::Vector3(1.0f, 0.0f, 0.0f),
                                                   RayLib::Vector3(-1.0f, 0.0f, 0.0f)};

        // foreach dir in directions:
        int mapIndexLeft = 0;
        int mapIndexRight = 0;

        for (auto dir = directions.begin(); dir != directions.end(); dir++) {
            mapIndexLeft = static_cast<int>(position.z + dir->z / 10);
            mapIndexRight = static_cast<int>(position.x + dir->x / 10);

            if (symbol == PLAYER && _playersmap[mapIndexLeft][mapIndexRight] == PLAYER) {
                _directionPath.push_back(*dir);
                return (_directionPath);
            }

            if (symbol >= BOX_HP_1 && symbol <= BOX_HP_3 && (_boxmap[mapIndexLeft][mapIndexRight] <= BOX_HP_1 && _boxmap[mapIndexLeft][mapIndexRight] <= BOX_HP_3)) {
                _directionPath.push_back(*dir);
                return (_directionPath);
            }

            if (_boxmap[mapIndexLeft][mapIndexRight] == EMPTY) {
                _directionPath.push_back(*dir);
                GeneratePathToSymbol(position + *dir, symbol);
                break;
            }
        }
        return (_directionPath);
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