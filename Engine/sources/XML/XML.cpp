/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** XML
*/

#include "XML.hpp"
#include "Vector3.hpp"
#include "Transform.hpp"

XMLException::XMLException(std::string value) :
_value(value)
{}

const char *XMLException::what() const noexcept
{
    return this->_value.c_str();
}

void XML::CreateWall(ECS::Entity& entity, boost::property_tree::ptree& xml)
{
    boost::property_tree::ptree position = xml.get_child("Transform").get_child("Position");

    int x = position.get<int>("x");
    int y = position.get<int>("y");
    int z = position.get<int>("z");

    entity.AddComponent<Component::Transform>(RayLib::Vector3(x, y, z));
}

void XML::CreatePlayer(ECS::Entity& entity, boost::property_tree::ptree& xml)
{
    boost::property_tree::ptree position = xml.get_child("Transform").get_child("Position");

    int x = position.get<int>("x");
    int y = position.get<int>("y");
    int z = position.get<int>("z");

    entity.AddComponent<Component::Transform>(RayLib::Vector3(x, y, z));
}

void XML::LoadMap(std::string path, ECS::Coordinator& coordinator)
{
    boost::property_tree::ptree tree;
    try
    {
        boost::property_tree::read_xml(path, tree);
    }
    catch (boost::property_tree::xml_parser_error& error)
    {
        throw XMLException("File at path doesn't exists");
    }

    try
    {
        for (boost::property_tree::ptree::value_type &child : tree.get_child("Entities"))
        {
            ECS::Entity &entity = coordinator.CreateEntity();

            if (child.first == "Wall")
                XML::CreateWall(entity, child.second);
            if (child.first == "Player")
                XML::CreatePlayer(entity, child.second);
        }
    }
    catch (boost::property_tree::ptree_bad_path& error)
    {
        throw XMLException("Parsing error");
    }
}
