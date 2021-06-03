/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Animator
*/

#include "Animator.hpp"

namespace Component
{
    Animator::Animator(const std::string& filePath, std::string stateName)
    {
        _stateMachine.insert(std::pair<std::string, RayLib::ModelAnimation>(stateName, RayLib::ModelAnimation(filePath)));
        _currentState = stateName;
    }

    void Animator::SetState(const std::string& state)
    {
        if (_stateMachine.find(state) != _stateMachine.end()) {
            _currentState = state;
        }
    }
    void Animator::PlayCurrentState(RayLib::Model& model)
    {
        _stateMachine.find(_currentState)->second.Play(model);
    }
}

