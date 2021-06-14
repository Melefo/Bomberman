/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Animator
*/

#include "Animator.hpp"
#include "AssetManager.hpp"

namespace Component
{
    Animator::Animator(const std::string& assetName, std::string stateName) : _currentState(stateName), _name(assetName)
    {
    }

    void Animator::SetState(const std::string& state)
    {
        _currentState = state;
    }

    void Animator::PlayCurrentState(RayLib::Model& model)
    {
        //! cache this
        std::unique_ptr<AssetManager> &assetManagerRef = AssetManager::GetInstance();
        Asset &asset = assetManagerRef->getAssetFromName(_name);
        std::map<std::string, RayLib::ModelAnimation> &animations = asset.getAnimations();

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
