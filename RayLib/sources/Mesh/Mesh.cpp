/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Mesh
*/

#include "Mesh.hpp"

namespace RayLib
{
    Mesh::Mesh(Vector3 scale)
    {
        _mesh = ::GenMeshCube(scale.x, scale.y, scale.z);
    }

    Mesh::Mesh(Image img, Vector3 scale)
    {
        _mesh = ::GenMeshCubicmap(img.GetImage(), scale.getVector3());
    }

    ::Mesh Mesh::GetMesh()
    {
        return (_mesh);
    }

    Mesh::~Mesh()
    {
        // ? si le mesh fait partie d'un model -> double free...
        //UnloadMesh(_mesh);
    }
}

