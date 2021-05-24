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
        _model = LoadModel(fileName.c_str());
        //if (model.meshCount == 0)
            // !throw error
    }

    void Model::DrawModel(Vector3 position, float scale, Color tint)
    {
        ::DrawModel(_model, position.getVector3(), scale, tint.getColor());
    }

    void Model::DrawModelEx(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint)
    {
        ::DrawModelEx(_model, position.getVector3(),
                             rotationAxis.getVector3(),
                             rotationAngle,
                             scale.getVector3(),
                             tint.getColor());
    }

    Model::~Model()
    {
        if (_model.meshCount > 0)
            UnloadModel(_model);
    }
}