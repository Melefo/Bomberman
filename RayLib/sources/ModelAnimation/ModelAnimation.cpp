/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** ModelAnimation
*/

#include "ModelAnimation.hpp"

namespace RayLib
{
    ModelAnimation::ModelAnimation(const std::string& fileName) : _animsCount(0), _frame(0)
    {

        //::ModelAnimation *anims = ::LoadModelAnimations(fileName.c_str(), &_animsCount);
        _modelAnimations = ::LoadModelAnimations(fileName.c_str(), &_animsCount);

        if (_modelAnimations == NULL) {
            // throw
        }
        //for (int i = 0; i < _animsCount; i++) {
        //    _modelAnimations.push_back(anims[i]);
        //}
    }

    ModelAnimation::~ModelAnimation()
    {
        //! ceci fait crash tout
        for (int i = 0; i < _animsCount; i++) {
            //::UnloadModelAnimation(_modelAnimations[i]);
        }
        //RL_FREE(_modelAnimations);
    }

    void ModelAnimation::Play(Model& model, int animationIndex)
    {
        _frame++;
        ::UpdateModelAnimation(model.GetModel(), _modelAnimations[animationIndex], _frame);
        if (_frame >= _modelAnimations[animationIndex].frameCount)
            _frame = 0;
    }
}

