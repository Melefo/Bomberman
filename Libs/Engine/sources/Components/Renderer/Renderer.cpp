/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Renderer
*/

#include "Renderer.hpp"

namespace Component
{
    Renderer::Renderer(const std::string& name) :
     _name(name)
    {
    }

    std::ostream& Renderer::operator<<(std::ostream& os)
    {
        os << "<Renderer>";
        os << "<AssetName>" << _name << "</AssetName>";
        os << "</Renderer>";
        return (os);
    }

    boost::property_tree::ptree& Renderer::operator<<(boost::property_tree::ptree &ptree)
    {
        boost::property_tree::ptree rendererTree = ptree.get_child("Renderer");

        _name = rendererTree.get<std::string>("AssetName");
        return (ptree);
    }

    const std::string &Renderer::getName() const
    {
        return (_name);
    }
}
