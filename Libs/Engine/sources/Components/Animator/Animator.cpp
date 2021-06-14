/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Animator
*/

#include "Animator.hpp"

namespace Component
{
    Animator::Animator(ECS::Entity& entity, const std::string& assetName, std::string stateName)
    : _currentState(stateName), _name(assetName), _entity(entity), _asset(AssetManager::GetInstance()->getAssetFromName(_name, entity.GetId()))
    {
    }

    void Animator::SetState(const std::string& state)
    {
        _currentState = state;
    }

    const std::string& Animator::GetState(void) const
    {
        return (_currentState);
    }

    void Animator::PlayCurrentState(RayLib::Model& model)
    {
        std::map<std::string, RayLib::ModelAnimation> &animations = _asset.getAnimations();

        if (animations.find(_currentState) == animations.end()) {
            // il est possible de juste pas avoir d'animations
            //throw ECS::Exception::ComponentException("No state found of name: " + _currentState);
            return;
        }

        animations.find(_currentState)->second.Play(model);
    }

    const std::string &Animator::getName() const
    {
        return (_name);
    }
}
