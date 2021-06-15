/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** BoundingBox
*/

#include "BoundingBox.hpp"

namespace RayLib
{
    BoundingBox::BoundingBox(Vector3 minVert, Vector3 maxVert)
    {
        _minVertex = minVert;
        _maxVertex = maxVert;
    }

    void BoundingBox::InitFromCube(Vector3 cubePos, Vector3 cubeScale)
    {
        _minVertex = Vector3(cubePos.x - cubeScale.x / 2.0f,
                             cubePos.y - cubeScale.y / 2.0f,
                             cubePos.z - cubeScale.z / 2.0f);
        _maxVertex = Vector3(cubePos.x + cubeScale.x / 2.0f,
                             cubePos.y + cubeScale.y / 2.0f,
                             cubePos.z + cubeScale.z / 2.0f);
    }

    BoundingBox::BoundingBox(const BoundingBox& other)
    {
        _minVertex = other._minVertex;
        _maxVertex = other._maxVertex;
    }

    BoundingBox& BoundingBox::operator=(const BoundingBox& other)
    {
        _minVertex = other._minVertex;
        _maxVertex = other._maxVertex;
        return (*this);
    }

    ::BoundingBox BoundingBox::GetBounds(void)
    {
        ::BoundingBox bounds = {_minVertex.getVector3(),
                                _maxVertex.getVector3()};

        return (bounds);
    }

    Vector3 BoundingBox::GetCenter(void)
    {
        //! jsais pas calculer ça, ni c'est vrmt necessaire
        return (Vector3());
    }
}

