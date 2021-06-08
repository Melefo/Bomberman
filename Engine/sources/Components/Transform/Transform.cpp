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

    std::ostream& Transform::operator<<(std::ostream& stream)
    {
        stream << "<Transform>" << std::endl;
        stream << "\t<position>" << std::endl;
        stream << "\t\t";
        //stream << position << std::endl;
        stream << "\t</position>" << std::endl;
        stream << "</Transform>" << std::endl;

        return (stream);
    }

}

