/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Mesh
*/

#include "Mesh.hpp"

namespace RayLib
{
    Mesh::Mesh(Vector3 scale) : _mesh(::GenMeshCube(scale.x, scale.y, scale.z)), _loaded(true)
    {
    }

    Mesh::Mesh(Image img, Vector3 scale) : _mesh(::GenMeshCubicmap(img.GetImage(), scale.getVector3())), _loaded(true)
    {
        _mesh = ::GenMeshCubicmap(img.GetImage(), scale.getVector3());
    }

    ::Mesh Mesh::GetMesh()
    {
        return (_mesh);
    }

    void Mesh::SetLoaded(bool loaded)
    {
        _loaded = loaded;
    }

    Mesh::~Mesh()
    {
        if (_loaded)
            ::UnloadMesh(_mesh);
        // ? si le mesh fait partie d'un model -> double free...
    }
}

