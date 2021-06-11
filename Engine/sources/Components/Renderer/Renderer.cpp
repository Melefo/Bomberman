/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Renderer
*/

#include "Renderer.hpp"

namespace Component
{
    Renderer::Renderer(const std::string& name, const std::string& modelPath) :
    _model(modelPath), _texture(), _name(name)
    {
        _model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, _texture);
    }

    Renderer::Renderer() :
    _model(RayLib::Mesh(RayLib::Vector3(1.0f, 1.0f, 1.0f))), _texture("../assets/models/cube/def_text.png"), _name()
    {
        _model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, _texture);
    }

    Renderer::Renderer(const std::string& name, const std::string& modelPath, const std::string& texturePath) :
    _model(modelPath), _texture(texturePath), _name(name)
    {
        _model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, _texture);
    }

    RayLib::Model& Renderer::GetModel()
    {
        return (_model);
    }

    std::ostream& Renderer::operator<<(std::ostream& os)
    {
        os << "<Renderer>";
        os << _model;
        os << _texture;
        os << "</Renderer>";
        return (os);
    }

    std::istream& Renderer::operator>>(std::istream& is)
    {
        boost::property_tree::ptree tree;
        boost::property_tree::xml_parser::read_xml(is, tree);

        this->operator<<(tree);
        return (is);
    }

    boost::property_tree::ptree& Renderer::operator<<(boost::property_tree::ptree &ptree)
    {
        boost::property_tree::ptree rendererTree = ptree.get_child("Renderer");

        _model << rendererTree;
        _texture << rendererTree;
        _model.SetMaterialTexture(0, MATERIAL_MAP_DIFFUSE, _texture);

        return (ptree);
    }

    const std::string &Renderer::getName() const
    {
        return (_name);
    }
}
