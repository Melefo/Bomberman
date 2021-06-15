/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AIAlgo
*/

#include "AIAlgo.hpp"
#include <limits>

namespace Component
{
    AIAlgo::AIAlgo(ECS::Entity &player, float moveSpeed, float dropDelay) : AController(player, moveSpeed, dropDelay),
    _ai_player(player), _state(), _entities(ECS::Coordinator::GetInstance()->GetEntities()),
    _speed(moveSpeed), _direction(), _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype")),
    _currentState(AIState::CHASE), _enabled(true)
    {
        if (_state.RunScript("../assets/AIAlgo.lua") != 0)
        {
            this->_enabled = false;
            std::cout << "Huh" << std::endl;
        }
        if (_state.RunScript("../assets/Pathfinding.lua") != 0)
            this->_enabled = false;
    }

    void AIAlgo::Update(double dt, ECS::Entity& entity)
    {
        if (!this->_enabled)
            return;
        AIMapsGenerator& mapGen = ECS::Coordinator::GetInstance()->GetSystem<AIMapsGenerator>();
        const std::vector<std::vector<int>>& bombMap = mapGen.GetBombMap();
        const std::vector<std::vector<int>>& playerMap = mapGen.GetPlayersMap();
        const std::vector<std::vector<int>>& boxMap = mapGen.GetBoxMap();

        Component::Transform &transform = _ai_player.GetComponent<Component::Transform>();
        /*if (!_ai_player.HasComponent<Component::Transform>() && !_ai_player.HasComponent<Component::DropBomb>())
            return;
        std::vector<int> p_pos = {0, 0, 0};
        int bloc_s = 10;

        p_pos[0] = (int) comp_pos.position.x / bloc_s;
        p_pos[2] = (int) comp_pos.position.z / bloc_s;
        if (_state.Call<bool>("is_safe", p_pos, _bombmap) == true) {
            if (_state.Call<bool>("is_close_to_box", p_pos, _boxmap, _bombmap) && _explotimer <= 0) {
                _dropBomb.InstantiateBomb(comp_pos.position, Explosion::ExplosionType::CIRCLE);
                _explotimer = 3;
                //std::cout << "go there" << std::endl;
            }
            _state.Call<int>("get_safe_direction", p_pos, _boxmap, _bombmap);
        } else {
            _state.Call<int>("get_safe_direction", p_pos, _boxmap, _bombmap);
        }
        _direction.x = _state.GetGlobal<float>("Xdir");
        _direction.z = _state.GetGlobal<float>("Zdir");
        if (_explotimer > 0)
            _explotimer -= _window->GetFrameTime();*/

        _state.Call("SetMapValues", bombMap, playerMap, boxMap);

        //lua_CFunction validNode = _state.GetGlobal<lua_CFunction>("IsPositionWalkable");

        RayLib::Vector2<int> targetPos;
        RayLib::Vector2<int> aiPos = GetAgentPos();
        std::vector<RayLib::Vector2<int>> mapPositions;

        //_state.Call("astar", PlayerPos, closestSymbolPos, aimapgen.GetBoxMap(), func);

        if (_currentState == AIState::IDLE) {
            _direction = RayLib::Vector3();
        }

        if (_currentState == AIState::HIDE) {
            targetPos = GetClosestSymbolPos(aiPos, boxMap, BoxMapValues::EMPTY);

            if (targetPos.x == aiPos.x && targetPos.y == aiPos.y)
                std::cout << "Could not find hiding pos" << std::endl;
            else
                std::cout << "Found hiding pos" << std::endl;

            mapPositions = GetMapAsPositions(boxMap);
            GetDirectionsList(aiPos, targetPos, mapPositions);

            _direction = _directionPath[0];
            if (_direction == RayLib::Vector3())
                _currentState = AIState::IDLE;

        }
        if (_currentState == AIState::CHASE) {
            targetPos = GetClosestSymbolPos(aiPos, boxMap , BoxMapValues::BOX);
            mapPositions = GetMapAsPositions(boxMap);
            GetDirectionsList(aiPos, targetPos, mapPositions);

            _direction = _directionPath[0];

            if (_direction == RayLib::Vector3())
                _currentState = AIState::ATTACK;

        }
        if (_currentState == AIState::ATTACK) {
            _dropBomb.InstantiateBomb(transform.position);
            _currentState = AIState::HIDE;
        }

        if (Engine::GameConfiguration::GetDebugMode())
            DebugPath(transform.position);

        _movement.direction = _direction * _speed;

        _movement.Update(dt, entity);
        _dropBomb.Update();
    }

    void AIAlgo::DebugPath(RayLib::Vector3 startPos)
    {
        RayLib::Vector3 currentPos = startPos;

        _window->DrawCubeWires(currentPos, 5.0f, RED);

        for (auto dir = _directionPath.begin(); dir != _directionPath.end(); dir++) {
            currentPos += *dir;
            _window->DrawCubeWires(currentPos + RayLib::Vector3(0.0f, 1.0f, 0.0f), 5.0f, RED);
        }
    }

    void AIAlgo::FixedUpdate(ECS::Entity& entity)
    {
        _movement.FixedUpdate(entity);
    }

    void AIAlgo::LateUpdate(double, ECS::Entity&)
    {

    }

    void AIAlgo::GetDirectionsList(RayLib::Vector2<int> aiPos, RayLib::Vector2<int> targetPos, const std::vector<RayLib::Vector2<int>>& mapPositions)
    {
        std::vector<RayLib::Vector2<int>> path = _state.Call<std::vector<RayLib::Vector2<int>>>("AStar", aiPos, targetPos, mapPositions);

        for (std::size_t i = 0; i < path.size(); i++) {
            //std::cout << "Path [" << i << "]: X: " << path[i].x << " Y: " << path[i].y << std::endl;
        }

        _directionPath.clear();

        for (auto pathNode = path.begin(); pathNode != path.end(); pathNode++) {

            //std::cout << "X: " << (*pathNode).x << " - " << aiPos.x << " = " << (*pathNode).x - aiPos.x << std::endl;
            //std::cout << "Y: " << (*pathNode).y << " - " << aiPos.y << " = " << (*pathNode).y - aiPos.y << std::endl;

            RayLib::Vector3 dirToAdd = RayLib::Vector3(static_cast<float>((*pathNode).x - aiPos.x), 0.0f, static_cast<float>((*pathNode).y - aiPos.y));

            _directionPath.push_back(dirToAdd);
            //std::cout << "Pushing to _dirPath: " << dirToAdd << std::endl;

            aiPos += *pathNode;
        }
    }

    RayLib::Vector2<int> AIAlgo::GetClosestSymbolPos(RayLib::Vector2<int> agentPos, const std::vector<std::vector<int>>& map, int symbol)
    {
        RayLib::Vector2<int> closestSymbol = agentPos;
        float closest = std::numeric_limits<float>::max();
        RayLib::Vector2<int> searchRadius(10, 10);

        RayLib::Vector2<int> currentPoint = agentPos - (searchRadius * 0.5f);

        RayLib::Vector2<int> maxPoint = agentPos;
        maxPoint += (searchRadius * 0.5f);

        if (currentPoint.x < 0)
            currentPoint.x = 0;
        if (currentPoint.y < 0)
            currentPoint.y = 0;

        if (maxPoint.y > static_cast<int>(map.size()))
            maxPoint.y = static_cast<int>(map.size());
        if (maxPoint.x > static_cast<int>(map[0].size()))
            maxPoint.x = static_cast<int>(map[0].size());

        /*for (std::size_t i = 0; i < map.size(); i++)
        {
            for (std::size_t j = 0; j < map[i].size(); j++)
                std::cout << std::setw(4) << map[i][j];
            std::cout << std::endl;
        }*/

        for (int y = currentPoint.y; y < maxPoint.y; y++) {
            for (int x = currentPoint.x; x < maxPoint.x; x++) {
                if (map[y][x] == symbol && _state.Call<bool>("SimpleIsWalkable", RayLib::Vector2<int>(x, y))) {
                    float dst = agentPos.Distance(RayLib::Vector2<int>(x, y));
                    if (dst < closest) {
                        closest = dst;
                        closestSymbol = RayLib::Vector2<int>(x, y);
                    }
                }
            }
        }
        return (closestSymbol);
    }

    RayLib::Vector2<int> AIAlgo::GetAgentPos(void)
    {
        Transform& transform = _ai_player.GetComponent<Transform>();


        return (RayLib::Vector2<int>(static_cast<int>(transform.position.x / 10.0f),
                                     static_cast<int>(transform.position.z / 10.0f)));
    }

    std::vector<RayLib::Vector2<int>> AIAlgo::GetMapAsPositions(const std::vector<std::vector<int>>& map)
    {
        std::vector<RayLib::Vector2<int>> result;

        for (std::size_t i = 0; i < map.size(); i++) {
            for (std::size_t j = 0; j < map[0].size(); j++) {
                result.push_back(RayLib::Vector2<int>(static_cast<int>(j), static_cast<int>(i)));
            }
        }
        return (result);
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