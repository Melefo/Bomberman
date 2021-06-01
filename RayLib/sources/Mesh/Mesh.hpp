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
    /**
     * @brief Mesh encapsulation
     * 
     */
    class Mesh {
        public:
            /**
             * @brief Construct a new Mesh object
             * Generates a cube with given scale
             * @param scale 
             */
            Mesh(Vector3 scale=Vector3(1.0f, 1.0f, 1.0f));

            /**
             * @brief Construct a new Mesh object
             * Generate a mesh based on the given image
             * cf example: https://www.raylib.com/examples/web/models/loader.html?name=models_cubicmap
             * @param image 
             * @param scale 
             */
            Mesh(Image image, Vector3 scale=Vector3(1.0f, 1.0f, 1.0f));

            /**
             * @brief Destroy the Mesh object
             * 
             */
            ~Mesh();

            /**
             * @brief Get the Mesh object as a raylib structure
             * 
             * @return ::Mesh 
             */
            ::Mesh GetMesh(void);

        protected:
        private:
            ::Mesh _mesh;
    };
}

#endif /* !MESH_HPP_ */
