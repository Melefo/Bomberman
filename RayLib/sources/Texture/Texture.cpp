/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Texture
*/

#include "Texture.hpp"
#include <iostream>

namespace RayLib
{
    Texture::Texture(const std::string& filename) : _texture(LoadTexture(filename.c_str())), _fileName(filename)
    {

    }

    Texture::Texture(Image image) : _texture(LoadTextureFromImage(image.GetImage())), _fileName("")
    {

    }

    void Texture::DrawTexture(Vector2<float> position, Color tint)
    {
        ::DrawTextureV(_texture, position.getVector2(), tint.getColor());
    }

    void Texture::DrawTextureEx(Vector2<float> position, float rotation, float scale, Color tint)
    {
        ::DrawTextureEx(_texture, position.getVector2(), rotation, scale, tint.getColor());
    }

    void Texture::DrawTextureRec(RayLib::Rectangle source, RayLib::Vector2<float> position, RayLib::Color col)
    {
        ::DrawTextureRec(_texture, source.GetRectangle(), position.getVector2(), col.getColor());
    }

    void Texture::DrawBillboard(RayLib::Camera3D camera, RayLib::Vector3 center, float size, Color tint)
    {
        ::DrawBillboard(camera.GetCamera(), _texture, center.getVector3(), size, tint.getColor());
    }

    ::Texture2D Texture::GetTexture()
    {
        return (_texture);
    }

    Texture::~Texture()
    {
        UnloadTexture(_texture);
    }

    std::ostream& Texture::operator<<(std::ostream& os)
    {
        os << "<Texture>";
        os << "<fileName>" << _fileName << "</fileName>";
        os << "</Texture>";
        return (os);
    }

    std::istream& Texture::operator>>(std::istream& is)
    {
        boost::property_tree::ptree tree;
        boost::property_tree::xml_parser::read_xml(is, tree);

        boost::property_tree::ptree tex = tree.get_child("Texture");

        _fileName = tex.get<std::string>("fileName");
        _texture = LoadTexture(_fileName.c_str());
        return (is);
    }

    boost::property_tree::ptree& Texture::operator<<(boost::property_tree::ptree &ptree)
    {
        boost::property_tree::ptree tex = ptree.get_child("Texture");

        _fileName = tex.get<std::string>("fileName");
        _texture = LoadTexture(_fileName.c_str());
        return (ptree);
    }

    const std::string& Texture::GetFileName() const
    {
        return (_fileName);
    }
}