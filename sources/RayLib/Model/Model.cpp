/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Model
*/

#include "Model.hpp"

namespace RayLib
{
    Model::Model(const std::string& fileName)
    {
        model = LoadModel(fileName.c_str());
        //if (model.meshCount == 0)
            // !throw error
    }

    Model::~Model()
    {
        if (model.meshCount > 0)
            UnloadModel(model);
    }
}