/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Mesh
*/

#include "Mesh.hpp"

namespace RayLib
{

    Mesh::Mesh(const std::string& path)
    {
        ::Model model = ::LoadModel(path.c_str());
        _mesh = model.meshes[0];
        _loaded = true;
    }

    Mesh::Mesh(Vector3 scale) : _mesh(::GenMeshCube(scale.x, scale.y, scale.z)), _loaded(true)
    {
    }

    Mesh::Mesh(float radius, int rings, int slices) : _mesh(::GenMeshSphere(radius, rings, slices)), _loaded(true)
    {

    }

    Mesh::Mesh(float width, float length, int resX, int resZ) : _mesh(::GenMeshPlane(width, length, resX, resZ)), _loaded(true)
    {

    }

    Mesh::Mesh(Image img, Vector3 scale) : _mesh(::GenMeshCubicmap(img.GetImage(), scale.getVector3())), _loaded(true)
    {
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

