/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** AIAlgo
*/

#include "AIAlgo.hpp"

namespace Component
{
    AIAlgo::AIAlgo(ECS::Entity &player, AIMapsGenerator& aimapgen, float moveSpeed) : _ai_player(player), _state(),
    _entities(ECS::Coordinator::GetInstance()->GetEntities()), _boxmap(aimapgen.GetBoxMap()), _playersmap(aimapgen.GetPlayersMap()),
    _bombpowmap(aimapgen.GetBombPowMap()), _bombtimermap(aimapgen.GetBombTimeMap()), _colliding(false), _speed(moveSpeed), _direction(),
    _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype")), _explotimer(0), _maps(aimapgen)
    {
        _state.RunScript("../Engine/sources/Components/AIAlgo/AIAlgo.lua");
    }

    void AIAlgo::Update(double, ECS::Entity&)
    {
        if (!_ai_player.HasComponent<Component::Transform>() && !_ai_player.HasComponent<Component::DropBomb>())
            return;
        Component::Transform &comp_pos = _ai_player.GetComponent<Component::Transform>();
        Component::DropBomb &drop_bomb = _ai_player.GetComponent<Component::DropBomb>();
        std::vector<int> p_pos = {0, 0, 0};
        //RayLib::Vector3 p_pos;
        int bloc_s = 10;

        p_pos[0] = (int) comp_pos.position.x / bloc_s;
        p_pos[2] = (int) comp_pos.position.z / bloc_s;
        if (_state.Call<bool>("is_safe", p_pos, _bombtimermap) == true) {
            //_state.Call<int>("get_safe_direction", p_pos, _boxmap, _bombtimermap);
        } else {
            _state.Call<int>("get_safe_direction", p_pos, _boxmap, _bombtimermap);
        }
        _direction.x = _state.GetGlobal<float>("Xdir");
        _direction.z = _state.GetGlobal<float>("Zdir");
        if (_state.Call<bool>("drop_a_bomb", p_pos, _boxmap) == true && _explotimer <= 0) {
            Component::Explosion& _bombexplo = drop_bomb.InstantiateBomb(comp_pos.position, Explosion::ExplosionType::CIRCLE, 10.0f);
            _explotimer = _bombexplo.GetExplosionTimer();
            //prblm l'ia a le droit de poser plusieurs bombes
        }
        if (_explotimer > 0)
            _explotimer -= _window->GetFrameTime();
        //envoyer la map en param (la boxmap)
        //PARSE DES MAPS
        //for (auto it = _entities.begin(); it != _entities.end();) {
        //    auto &entity = *it->get();
        //    it++;
        //    AssignEntityToMap(entity);
        //}
        //ASSIGN _ai_player to playersmap
        // HORS OU DANS LE CPP et donc HORS OU DANS LE LUA
        //FAIRE L'ALGO (le + fun je suppose)
        //RETOURNER UNE VALEUR DE DEPLACEMENT
        //DROP UNE BOMBE S'IL FAUT
    }

    void AIAlgo::SlipperyCollisions(Component::Transform &comp_pos)
    {
        RayLib::Vector3 targetPosition = comp_pos.position + _direction * _speed;
        std::vector<std::reference_wrapper<Collider>> colliders = _ai_player.OfType<Collider>();
        RayLib::Vector3 modifiedDir = _direction;

        _colliding = false;
        for (auto it = colliders.begin(); it != colliders.end(); it++) {
            if (!_colliding)
                _colliding = it->get().IsCollidingAtPosition(targetPosition);
        }

        if (!_colliding)
            return;

        std::vector<RayLib::Vector3> newDirections;
        // check x solo
        newDirections.push_back(RayLib::Vector3(_direction.x, 0.0f, 0.0f));
        // check z solo
        newDirections.push_back(RayLib::Vector3(0.0f, 0.0f, _direction.z));

        if (abs(_direction.z) < 0.1f && abs(_direction.x) > 0.1f) {
            newDirections.push_back(RayLib::Vector3(_direction.x, 0.0f, -_direction.x));
            newDirections.push_back(RayLib::Vector3(_direction.x, 0.0f, _direction.x));
        }
        if (abs(_direction.x) < 0.1f && abs(_direction.z) > 0.1) {
            newDirections.push_back(RayLib::Vector3(_direction.z, 0.0f, _direction.z));
            newDirections.push_back(RayLib::Vector3(-_direction.z, 0.0f, _direction.z));
        }

        for (auto it = newDirections.begin(); it != newDirections.end(); it++) {
            if (it->x == 0.0f && it->z == 0.0f)
                continue;
            if (!CheckCollidersPos(colliders, comp_pos.position + *it * _speed)) {
                _colliding = false;
                _direction = *it;
                return;
            }
        }
    }

    bool AIAlgo::CheckCollidersPos(std::vector<std::reference_wrapper<Collider>> colliders, RayLib::Vector3 position)
    {
        for (auto it = colliders.begin(); it != colliders.end(); it++) {
            if (it->get().IsCollidingAtPosition(position))
                return (true);
        }
        return (false);
    }

    void AIAlgo::FixedUpdate(ECS::Entity&)
    {
        if (!_ai_player.HasComponent<Component::PhysicsBody>() && !_ai_player.HasComponent<Component::Transform>())
            return;
        Component::PhysicsBody &pb = _ai_player.GetComponent<Component::PhysicsBody>();
        Component::Transform &comp_pos = _ai_player.GetComponent<Component::Transform>();
        
        SlipperyCollisions(comp_pos);
        if (!_colliding) {
            pb.velocity = _direction * _speed;
        } else {
            pb.velocity = RayLib::Vector3();
        }
    }

    void AIAlgo::LateUpdate(double, ECS::Entity&)
    {

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