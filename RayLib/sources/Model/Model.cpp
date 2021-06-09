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

    Model::Model(Mesh mesh)
    {
        _model = ::LoadModelFromMesh(mesh.GetMesh());
        mesh.SetLoaded(false);
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

    const ::Model Model::GetModel()
    {
        return (_model);
    }

    Model::~Model()
    {
        if (_model.meshCount > 0)
            UnloadModel(_model);
    }

    std::ostream& Model::operator<<(std::ostream& os)
    {
        os << "<Model>";
        os << "<fileName>" << _fileName << "</fileName>";
        os << "</Model>";
        return (os);
    }

    std::istream& Model::operator>>(std::istream& is)
    {
        boost::property_tree::ptree tree;
        boost::property_tree::xml_parser::read_xml(is, tree);

        boost::property_tree::ptree tex = tree.get_child("Model");

        _fileName = tex.get<std::string>("fileName");
        _model = LoadModel(_fileName.c_str());
        return (is);
    }

    boost::property_tree::ptree& Model::operator<<(boost::property_tree::ptree &ptree)
    {
        boost::property_tree::ptree tex = ptree.get_child("Model");

        _fileName = tex.get<std::string>("fileName");
        _model = LoadModel(_fileName.c_str());
        return (ptree);
    }

    const std::string& Model::GetFileName() const
    {
        return (_fileName);
    }
}