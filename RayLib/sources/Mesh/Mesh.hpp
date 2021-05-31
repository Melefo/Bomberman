/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Mesh
*/
#ifndef MESH_HPP_
#define MESH_HPP_

#include <raylib.h>
#include "Image.hpp"
#include "Vector3.hpp"

namespace RayLib
{
    class Mesh {
        public:
            Mesh(Vector3 scale=Vector3(1.0f, 1.0f, 1.0f));
            //Mesh GenMeshCube(float width, float height, float length);                                         // Generate cuboid mesh
            //Mesh GenMeshCubicmap(Image cubicmap, Vector3 cubeSize);                                            // Generate cubes-based map mesh from image data
            Mesh(Image image, Vector3 scale=Vector3(1.0f, 1.0f, 1.0f));

            ~Mesh();

            ::Mesh GetMesh(void);

        protected:
        private:
            ::Mesh _mesh;
    };
}

#endif /* !MESH_HPP_ */
