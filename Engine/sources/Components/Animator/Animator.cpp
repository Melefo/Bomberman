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
    Animator::Animator(const std::string& filePath, std::string stateName) : _currentState(stateName)
    {
        _stateMachine.insert(std::pair<std::string, RayLib::ModelAnimation>(stateName, RayLib::ModelAnimation(filePath)));
        _name = Asset::getFileNameWithoutExt(filePath);
        if (_name.find("_anim") != std::string::npos)
            _name = _name.substr(0, _name.find("_anim"));
    }

    void Animator::SetState(const std::string& state)
    {
        if (_stateMachine.find(state) != _stateMachine.end()) {
            _currentState = state;
        }
    }

    void Animator::PlayCurrentState(RayLib::Model& model)
    {
        //! cache this
        std::unique_ptr<AssetManager> &assetManagerRef = AssetManager::GetInstance();
        Asset &asset = assetManagerRef->getAssetFromName(_name);
        std::map<std::string, RayLib::ModelAnimation> &animations = asset.getAnimations();
        
        animations.find(_currentState)->second.Play(model);
        //_stateMachine.find(_currentState)->second.Play(model);
    }

    void Animator::AddAnimation(const std::string& filePath, std::string stateName)
    {
        _stateMachine.insert(std::pair<std::string, RayLib::ModelAnimation>(stateName, RayLib::ModelAnimation(filePath)));
    }

    const std::string &Animator::getName() const
    {
        return (_name);
    }
}
