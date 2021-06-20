/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Animator
*/

#include "Animator.hpp"

namespace Component
{
    Animator::Animator(ECS::Entity& entity, const std::string& path, std::string stateName)
    : _currentState(stateName),  _entity(entity)
    {
        _stateMachine[stateName] = AssetCache::GetAsset<RayLib::ModelAnimation>(path);
    }

    void Animator::SetState(const std::string& state)
    {
        _currentState = state;
    }

    void Animator::AddState(const std::string& path, std::string state)
    {
        _stateMachine[state] = AssetCache::GetAsset<RayLib::ModelAnimation>(path);
    }

    const std::string& Animator::GetState(void) const
    {
        return (_currentState);
    }

    void Animator::PlayCurrentState(RayLib::Model& model)
    {
        if (_stateMachine.find(_currentState) == _stateMachine.end()) {
            // il est possible de juste pas avoir d'animations
            //throw ECS::Exception::ComponentException("No state found of name: " + _currentState);
            return;
        }
        _stateMachine.find(_currentState)->second->Play(model);
    }
}
