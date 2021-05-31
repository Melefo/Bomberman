/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Model
*/

#include "Model.hpp"
#include <iostream>

namespace RayLib
{
    Model::Model(const std::string& fileName)
    {
        _model = LoadModel(fileName.c_str());
        //if (model.meshCount == 0)
            // !throw error
    }

    Model::Model(Mesh mesh)
    {
        _model = ::LoadModelFromMesh(mesh.GetMesh());
    }

    void Model::Draw(Vector3 position, float scale, Color tint)
    {
        ::DrawModel(_model, position.getVector3(), scale, tint.getColor());
    }

    void Model::DrawEx(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint)
    {
        ::DrawModelEx(_model, position.getVector3(),
                             rotationAxis.getVector3(),
                             rotationAngle,
                             scale.getVector3(),
                             tint.getColor());
    }

    void Model::SetMaterialTexture(int matIndex, int mapType, Texture& text)
    {
        ::SetMaterialTexture(&_model.materials[matIndex], mapType, text.GetTexture());

        //_model.materials[matIndex].maps[mapType].texture = text.GetTexture();                 // Set map diffuse texture

    }

    Model::~Model()
    {
        if (_model.meshCount > 0)
            UnloadModel(_model);
    }
}