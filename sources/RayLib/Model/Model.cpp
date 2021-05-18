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

    void Model::DrawModel(Vector3 position, float scale, Color tint)
    {
        ::DrawModel(model, {position.x, position.y, position.z}, scale, {tint.r, tint.g, tint.b, tint.a});
    }

    void Model::DrawModelEx(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint)
    {
        ::DrawModelEx(model, {position.x, position.y, position.z},
                             {rotationAxis.x, rotationAxis.y, rotationAxis.z},
                             rotationAngle,
                             {scale.x, scale.y, scale.z},
                             {tint.r, tint.g, tint.b, tint.a});
    }

    Model::~Model()
    {
        if (model.meshCount > 0)
            UnloadModel(model);
    }
}