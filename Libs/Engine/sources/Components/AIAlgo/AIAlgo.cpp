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
    _currentState(AIState::HIDE), _enabled(true), _stateDuration(0.75f), _timeToStateChange(0.75f)
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

        _state.Call("SetMapValues", playerMap, boxMap);

        //lua_CFunction validNode = _state.GetGlobal<lua_CFunction>("IsPositionWalkable");

        RayLib::Vector2<int> targetPos;
        RayLib::Vector2<int> aiPos = GetAgentPos();
        std::vector<RayLib::Vector2<int>> mapPositions;

        //_state.Call("astar", PlayerPos, closestSymbolPos, aimapgen.GetBoxMap(), func);

        if (_dropBomb.timeToDrop > 0.0f) {
            _dropBomb.timeToDrop -= _window->GetFrameTime();
        }

        if (_timeToStateChange <= 0.0f) {
            /*for (std::size_t i = 0; i < boxMap.size(); i++) {
                for (std::size_t j = 0; j < boxMap[i].size(); j++) {
                    std::cout << std::setw(4) << boxMap[i][j];
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;*/
            switch (this->_currentState)
            {
            case AIState::IDLE:
                _direction = RayLib::Vector3();
                break;
            case AIState::HIDE:
                targetPos = GetClosestSymbolPos(aiPos, boxMap, BoxMapValues::EMPTY);

                if (targetPos.x == aiPos.x && targetPos.y == aiPos.y)
                    std::cout << "Could not find hiding pos" << std::endl;
                else
                    std::cout << "Found hiding pos\nTarget X : " << targetPos.x << " / Target Y : " << targetPos.y << std::endl;

                mapPositions = GetMapAsPositions(boxMap);
                GetDirectionsList(aiPos, targetPos, mapPositions);

                _direction = _directionPath[0];
                if (_direction == RayLib::Vector3())
                    _currentState = AIState::CHASE;
                break;
            case AIState::CHASE:
                targetPos = GetClosestSymbolPos(aiPos, boxMap, BoxMapValues::BOX);
                mapPositions = GetMapAsPositions(boxMap);
                GetDirectionsList(aiPos, targetPos, mapPositions);

                _direction = _directionPath[0];
                if (aiPos.x + _direction.x == targetPos.x && aiPos.y + _direction.z == targetPos.y)
                    _currentState = AIState::ATTACK;
                break;
            case AIState::ATTACK:
                if (boxMap[aiPos.y][aiPos.x + 1] != BoxMapValues::EMPTY && boxMap[aiPos.y][aiPos.x - 1] != BoxMapValues::EMPTY && boxMap[aiPos.y + 1][aiPos.x] != BoxMapValues::EMPTY && boxMap[aiPos.y - 1][aiPos.x] != BoxMapValues::EMPTY) {
                    _currentState = AIState::HIDE;
                    break;
                }
                if (_dropBomb.timeToDrop <= 0.0f) {
                    _dropBomb.InstantiateBomb(RayLib::Vector3(std::round(transform.position.x / 10) * 10, std::round(transform.position.y / 10) * 10, std::round(transform.position.z / 10) * 10));
                    _dropBomb.timeToDrop = _dropBomb.GetDropDelay();
                }
                _currentState = AIState::HIDE;
                _direction = RayLib::Vector3();
                break;
            }

            _movement.direction = _direction * (_speed);

            _timeToStateChange = _stateDuration;
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

    void AIAlgo::DebugPath(std::vector<RayLib::Vector2<int>> path)
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
            RayLib::Vector3 position = RayLib::Vector3(static_cast<float>(node.x), 0.0f, static_cast<float>(node.y));
            position = position * 10.0f;
            position += RayLib::Vector3(0.0f, 1.0f, 0.0f);
            _window->DrawSphereWires(position, 7.5f, 20, 20, col);
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

        if (Engine::GameConfiguration::GetDebugMode()) {
            DebugPath(path);
        }

        _directionPath.clear();

        for (auto &pathNode : path) {

            //std::cout << "X: " << (*pathNode).x << " - " << aiPos.x << " = " << (*pathNode).x - aiPos.x << std::endl;
            //std::cout << "Y: " << (*pathNode).y << " - " << aiPos.y << " = " << (*pathNode).y - aiPos.y << std::endl;

            if (pathNode.x == aiPos.x && pathNode.y == aiPos.y)
                continue;
            RayLib::Vector3 dirToAdd = RayLib::Vector3(static_cast<float>(pathNode.x - aiPos.x), 0.0f, static_cast<float>(pathNode.y - aiPos.y));

            _directionPath.push_back(dirToAdd);
            //std::cout << "Pushing to _dirPath: " << dirToAdd << std::endl;

            aiPos = pathNode;
        }
        if (_directionPath.size() == 0)
            _directionPath.push_back(RayLib::Vector3(0, 0, 0));
    }

    RayLib::Vector2<int> AIAlgo::GetClosestSymbolPos(RayLib::Vector2<int> agentPos, const std::vector<std::vector<int>>& map, int symbol)
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
        /*for (std::size_t i = 0; i < map.size(); i++)
        {
            for (std::size_t j = 0; j < map[i].size(); j++)
                std::cout << std::setw(4) << map[i][j];
            std::cout << std::endl;
        }*/

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
}