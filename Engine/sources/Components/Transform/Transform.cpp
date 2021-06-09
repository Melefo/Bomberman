/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Transform
*/

#include "Transform.hpp"

namespace Component
{
    Transform::Transform(RayLib::Vector3 startPos, RayLib::Vector3 startRot, RayLib::Vector3 startScale):
    position(startPos), rotation(startRot), scale(startScale)
    {
    }

    std::ostream &Transform::operator<<(std::ostream &os)
    {
        os << "<Transform>";
        os << "<position>" << position << "</position>";
        os << "<rotation>" << rotation << "</rotation>";
        os << "<scale>" << scale << "</scale>";
        os << "</Transform>";
        return (os);
    }

    std::istream &Transform::operator>>(std::istream &is)
    {
        boost::property_tree::ptree tree;
        boost::property_tree::xml_parser::read_xml(is, tree);

        boost::property_tree::ptree transformTree = tree.get_child("Transform");
        boost::property_tree::ptree& positionTree = transformTree.get_child("position");
        boost::property_tree::ptree& rotationTree = transformTree.get_child("rotation");
        boost::property_tree::ptree& scaleTree = transformTree.get_child("scale");

        position << positionTree;
        rotation << rotationTree;
        scale << scaleTree;
        return (is);
    }

    boost::property_tree::ptree& Transform::operator<<(boost::property_tree::ptree &ptree)
    {
        boost::property_tree::ptree transformTree = ptree.get_child("Transform");
        boost::property_tree::ptree& positionTree = transformTree.get_child("position");
        boost::property_tree::ptree& rotationTree = transformTree.get_child("rotation");
        boost::property_tree::ptree& scaleTree = transformTree.get_child("scale");

        position << positionTree;
        rotation << rotationTree;
        scale << scaleTree;
        return (ptree);
    }

}

