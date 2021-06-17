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
    Model::Model(const std::string& fileName) : _model(LoadModel(fileName.c_str())), _fileName(fileName)
    {

    }

    Model::Model()
    {
        Mesh mesh;
        mesh.SetLoaded(false);

        _model = ::LoadModelFromMesh(mesh.GetMesh());
    }


    Model::Model(Mesh& mesh)
    {
        _model = ::LoadModelFromMesh(mesh.GetMesh());
        mesh.SetLoaded(false);
    }

    void Model::Draw(Vector3 position, Vector3 scale, Color tint)
    {
        ::DrawModelEx(_model, position.getVector3(), Vector3().getVector3(), 0.0f, scale.getVector3(), tint.getColor());
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

    void Model::SetMaterialShader(int matIndex, Shader& shader)
    {
        _model.materials[matIndex].shader = shader.GetShader();
    }

    const ::Model Model::GetModel()
    {
        return (_model);
    }

    Model::~Model()
    {
        if (_model.meshCount > 0) {
            ::UnloadModelKeepMeshes(_model);
        }
    }

    const std::string& Model::GetFileName() const
    {
        return (_fileName);
    }

    void Model::RotateModel(RayLib::Vector3 rotation)
    {
        _model.transform = MatrixRotateXYZ((rotation * DEG2RAD).getVector3());
    }
}