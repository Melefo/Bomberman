/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Destructible
*/

#include "Destructible.hpp"

namespace Component
{
    Destructible::Destructible(ECS::Entity& entity, int resistance) : _myEntity(entity), _resistance(resistance)
    {
    }

    int Destructible::GetResistance()
    {
        return (_resistance);
    }

    void Destructible::TakeDamage(int damage)
    {
        _resistance -= damage;

        if (_resistance <= 0) {
            _resistance = 0;
            _myEntity.Dispose();
        }
    }

    std::ostream &Destructible::operator<<(std::ostream &os)
    {
        os << "<Destructible>";
        os << "<_resistance>" << _resistance << "</_resistance>";
        os << "</Destructible>";
        return (os);
    }

    std::istream &Destructible::operator>>(std::istream &is)
    {
        boost::property_tree::ptree tree;
        boost::property_tree::xml_parser::read_xml(is, tree);

        this->operator<<(tree);
        return (is);
    }

    boost::property_tree::ptree& Destructible::operator<<(boost::property_tree::ptree &ptree)
    {
        boost::property_tree::ptree node = ptree.get_child("Destructible");

        _resistance = node.get<int>("_resistance");
        return (ptree);
    }

}
