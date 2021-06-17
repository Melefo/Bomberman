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
#include "IAsset.hpp"

namespace RayLib
{
    /**
     * @brief Mesh encapsulation
     * 
     */
    class Mesh : public IAsset {
        public:

            Mesh(const std::string& path);

            /**
             * @brief Construct a new Mesh object
             * Generates a cube with given scale
             * @param scale 
             */
            Mesh(Vector3 scale=Vector3(1.0f, 1.0f, 1.0f));
            /**
             * @brief Construct a new Mesh object
             * 
             * @param radius 
             * @param rings 
             * @param slices 
             */
            Mesh(float radius, int rings, int slices);
            /**
             * @brief Construct a new Mesh object
             * 
             * @param width 
             * @param length 
             * @param resX 
             * @param resZ 
             */
            Mesh(float width, float length, int resX, int resZ);

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
            ~Mesh() override;

            /**
             * @brief Get the Mesh object as a raylib structure
             * 
             * @return ::Mesh 
             */
            ::Mesh GetMesh(void);

            /**
             * @brief Set the Loaded boolean
             * If the mesh is part of a model, it should not be unloaded a second time
             * @param loaded 
             */
            void SetLoaded(bool loaded);

        protected:
        private:
            ::Mesh _mesh;
            bool _loaded;
    };
}

#endif /* !MESH_HPP_ */
