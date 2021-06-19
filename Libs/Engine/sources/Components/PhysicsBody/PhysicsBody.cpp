/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsBody
*/

#include "PhysicsBody.hpp"

namespace Component
{
    PhysicsBody::PhysicsBody() : velocity()
    {
    }

    std::ostream &PhysicsBody::operator<<(std::ostream &os)
    {
        os << "<PhysicsBody></PhysicsBody>";
        return (os);
    }

    boost::property_tree::ptree& PhysicsBody::operator<<(boost::property_tree::ptree &ptree)
    {
        return (ptree);
    }
}