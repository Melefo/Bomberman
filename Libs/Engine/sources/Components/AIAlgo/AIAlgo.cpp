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
    _currentState(AIState::HIDE), _enabled(true), _stateDuration(0.75f), _timeToStateChange(0.35f)
    {

        if (_state.RunScript("../assets/Pathfinding.lua") != 0)
            this->_enabled = false;
    }

    void AIAlgo::Update(double dt, ECS::Entity& entity)
    {
        if (!this->_enabled)
            return;
        AIMapsGenerator& mapGen = ECS::Coordinator::GetInstance()->GetSystem<AIMapsGenerator>();
        const std::vector<std::vector<int>>& playerMap = mapGen.GetPlayersMap();
        const std::vector<std::vector<int>>& boxMap = mapGen.GetBoxMap();

        Component::Transform &transform = _ai_player.GetComponent<Component::Transform>();

        _state.Call("SetMapValues", playerMap, boxMap);

        //lua_CFunction validNode = _state.GetGlobal<lua_CFunction>("IsPositionWalkable");

        RayLib::Vector2<int> targetPos;
        RayLib::Vector2<int> aiPos = GetAgentPos();
        std::vector<RayLib::Vector2<int>> mapPositions;

        if (_dropBomb.timeToDrop > 0.0f) {
            _dropBomb.timeToDrop -= _window->GetFrameTime();
        }

        //if (boxMap[transform.position.z][transform.position.x] >= BombMapValues::BOMB)
        //    _currentState = AIState::HIDE;
        if (_timeToStateChange <= 0.0f) {
            switch (this->_currentState)
            {
            case AIState::IDLE:
                _direction = RayLib::Vector3();
                break;
            case AIState::HIDE:
                std::cout << "HIDE" << std::endl;
                mapPositions = GetMapAsPositions(boxMap);
                targetPos = GetBestPos(aiPos, boxMap, mapPositions, BoxMapValues::EMPTY);
                GetDirectionsList(aiPos, targetPos, mapPositions, boxMap);

                _direction = _directionPath[0];
                if (_direction == RayLib::Vector3())
                    _currentState = AIState::CHASE;
                break;
            case AIState::CHASE:
                std::cout << "CHASE" << std::endl;
                mapPositions = GetMapAsPositions(boxMap);
                targetPos = GetBestPos(aiPos, boxMap, mapPositions, BoxMapValues::BOX);
                GetDirectionsList(aiPos, targetPos, mapPositions, boxMap);

                _direction = _directionPath[0];
                std::cout << "aiPos: " << aiPos.x << " " << aiPos.y << std::endl;
                std::cout << "direc: " << _direction.x << " " << _direction.z << std::endl;
                if (aiPos.x + _direction.x == targetPos.x && aiPos.y + _direction.z == targetPos.y)
                    _currentState = AIState::ATTACK;
                break;
            case AIState::ATTACK:
                std::cout << "ATTACK" << std::endl;
                /*if (boxMap[aiPos.y][aiPos.x + 1] != BoxMapValues::EMPTY && boxMap[aiPos.y][aiPos.x - 1] != BoxMapValues::EMPTY && boxMap[aiPos.y + 1][aiPos.x] != BoxMapValues::EMPTY && boxMap[aiPos.y - 1][aiPos.x] != BoxMapValues::EMPTY) {
                    _currentState = AIState::HIDE;
                    break;
                }*/
                if (_dropBomb.timeToDrop <= 0.0f) {
                    _dropBomb.InstantiateBomb(RayLib::Vector3(std::round(transform.position.x / 10) * 10, std::round(transform.position.y / 10) * 10, std::round(transform.position.z / 10) * 10));
                    _dropBomb.timeToDrop = _dropBomb.GetDropDelay();
                }
                _currentState = AIState::HIDE;
                _direction = RayLib::Vector3();
                break;
            }

            _movement.direction = _direction * (_speed);

            _timeToStateChange = 0.60f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.90f-0.60f)));;
        } else {
            _timeToStateChange -= _window->GetFrameTime();
        }
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

    void AIAlgo::DebugPath(std::vector<RayLib::Vector2<int>> path, RayLib::Vector2<int> targetPos)
    {
        RayLib::Color col;

        switch (this->_currentState)
        {
        case AIState::IDLE:
            col = BLUE;
            break;
        case AIState::HIDE:
            col = GREEN;
            break;
        case AIState::CHASE:
            col = ORANGE;
            break;
        case AIState::ATTACK:
            col = RED;
            break;
        }

        for (auto &node : path) {
            RayLib::Vector3 position = RayLib::Vector3(node.x, 0.0f, node.y);
            position = position * 10.0f;
            position += RayLib::Vector3(0.0f, 1.0f, 0.0f);
            _window->DrawSphereWires(position, 7.5f, 20, 20, col);
        }
        col = BLUE;
        RayLib::Vector3 posi = RayLib::Vector3(targetPos.x, 0.0f, targetPos.y);
        posi = posi * 10.0f;
        posi += RayLib::Vector3(0.0f, 1.0f, 0.0f);
        _window->DrawSphereWires(posi, 7.5f, 20, 20, col);
    }


    void AIAlgo::FixedUpdate(ECS::Entity& entity)
    {
        _movement.FixedUpdate(entity);
    }

    void AIAlgo::LateUpdate(double, ECS::Entity&)
    {

    }

    void AIAlgo::GetDirectionsList(RayLib::Vector2<int> aiPos, RayLib::Vector2<int> targetPos, const std::vector<RayLib::Vector2<int>>& mapPositions, const std::vector<std::vector<int>>& map)
    {
        std::vector<RayLib::Vector2<int>> path = _state.Call<std::vector<RayLib::Vector2<int>>>("AStar", aiPos, targetPos, mapPositions);

        if (Engine::GameConfiguration::GetDebugMode()) {
            DebugPath(path, targetPos);
        }

        _directionPath.clear();
        for (auto &pathNode : path) {
            if (map[pathNode.y][pathNode.x] >= 0 && _currentState != AIState::HIDE) {
                _directionPath.clear();
                _directionPath.push_back(RayLib::Vector3(0, 0, 0));
                return;
            }
            if (pathNode.x == aiPos.x && pathNode.y == aiPos.y)
                continue;
            RayLib::Vector3 dirToAdd = RayLib::Vector3(static_cast<float>(pathNode.x - aiPos.x), 0.0f, static_cast<float>(pathNode.y - aiPos.y));

            _directionPath.push_back(dirToAdd);

            aiPos = pathNode;
        }
        if (_directionPath.size() == 0)
            _directionPath.push_back(RayLib::Vector3(0, 0, 0));
    }

    RayLib::Vector2<int> AIAlgo::GetBestPos(RayLib::Vector2<int> agentPos, const std::vector<std::vector<int>>& map, const std::vector<RayLib::Vector2<int>>& mapPositions, int value)
    {
        RayLib::Vector2<int> closestSymbol = agentPos;
        RayLib::Vector2<int> maxPoint = agentPos;
        RayLib::Vector2<int> minPoint = agentPos;
        std::vector<RayLib::Vector2<int>> path;
        RayLib::Vector2<int> searchRadius(map.size(), map.size());
        float closest = std::numeric_limits<float>::max();

        maxPoint += (searchRadius * 0.5f);
        minPoint -= (searchRadius * 0.5f);

        if (maxPoint.y > static_cast<int>(map.size()))
            maxPoint.y = static_cast<int>(map.size());
        if (maxPoint.x > static_cast<int>(map[0].size()))
            maxPoint.x = static_cast<int>(map[0].size());
        if (minPoint.y < 0)
            minPoint.y = 0;
        if (minPoint.x < 0)
            minPoint.x = 0;

        for (int y = minPoint.y; y < maxPoint.y; y++) {
            for (int x = minPoint.x; x < maxPoint.x; x++) {
                if (map[y][x] == value) {
                    path = _state.Call<std::vector<RayLib::Vector2<int>>>("AStar", agentPos, (RayLib::Vector2<int>(x, y)), mapPositions);
                    if (path.back().x != x && path.back().y != y)
                        continue;
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

        return (RayLib::Vector2<int>(static_cast<int>(std::lround(transform.position.x / 10.0f)),
                                     static_cast<int>(std::lround(transform.position.z / 10.0f))));
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

    /*RayLib::Vector2<int> AIAlgo::GetClosestSymbolPos(RayLib::Vector2<int> agentPos, const std::vector<std::vector<int>>& map, int symbol)
    {
        RayLib::Vector2<int> closestSymbol = agentPos;
        float closest = std::numeric_limits<float>::max();
        RayLib::Vector2<int> searchRadius(100, 100);

        RayLib::Vector2<int> maxPoint = agentPos;
        RayLib::Vector2<int> minPoint = agentPos;
        maxPoint += (searchRadius * 0.5f);
        minPoint -= (searchRadius * 0.5f);

        if (maxPoint.y > static_cast<int>(map.size()))
            maxPoint.y = static_cast<int>(map.size());
        if (maxPoint.x > static_cast<int>(map[0].size()))
            maxPoint.x = static_cast<int>(map[0].size());
        if (minPoint.y < 0)
            minPoint.y = 0;
        if (minPoint.x < 0)
            minPoint.x = 0;

        for (int y = minPoint.y; y < maxPoint.y; y++) {
            for (int x = minPoint.x; x < maxPoint.x; x++) {
                if (map[y][x] == symbol) {

                    float dst = agentPos.Distance(RayLib::Vector2<int>(x, y));
                    if (dst < closest) {
                        closest = dst;
                        closestSymbol = RayLib::Vector2<int>(x, y);
                    }
                }
            }
        }
        return (closestSymbol);
    }*/
}