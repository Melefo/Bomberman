/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** testEntitySerializer
*/

#include <criterion/criterion.h>
#include "Vector3.hpp"
#include "IXMLSerializable.hpp"

Test(serializeVec3, vec3)
{
    RayLib::Vector3 src(1.0f, 2.0f, 3.0f);
    RayLib::Vector3 dest = RayLib::Vector3();

    IXMLSerializable& serializableObj = src;
    std::ostringstream oss;
    std::istringstream iss;

    oss << serializableObj;
    iss.str(oss.str());
    iss >> dest;
    cr_assert(src == dest);
}