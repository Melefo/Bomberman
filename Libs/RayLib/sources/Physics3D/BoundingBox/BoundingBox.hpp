/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** BoundingBox
*/

#ifndef BOUNDINGBOX_HPP_
#define BOUNDINGBOX_HPP_

#include "Vector3.hpp"

namespace RayLib
{
    /**
     * @brief Boundingbox encapsulation
     * 
     */
    class BoundingBox {
        public:
            /**
             * @brief Construct a new Bounding Box object
             * constructs a box from minVertex and maxVertex
             * @param minVert 
             * @param maxVert 
             */
            BoundingBox(Vector3 minVert, Vector3 maxVert);

            /**
             * @brief Construct a new Bounding Box object
             * 
             * @param other 
             */
            BoundingBox(const BoundingBox& other);

            /**
             * @brief Destroy the Bounding Box object
             * 
             */
            ~BoundingBox() = default;

            /**
             * @brief Create a box from a cube's position and scale
             * Not a constructor, because it has the same parameters (ambiguous reference)
             * @param cubePos 
             * @param cubeScale 
             */
            void InitFromCube(Vector3 cubePos, Vector3 cubeScale);

            /**
             * @brief Assigment operator
             * 
             * @param other 
             * @return BoundingBox& 
             */
            BoundingBox& operator=(const BoundingBox& other);

            /**
             * @brief Get the Bounds as a raylib structure
             * 
             * @return ::BoundingBox 
             */
            ::BoundingBox GetBounds(void);

            /**
             * @brief Get the box's center position
             * not yet implemented
             * @return Vector3
             */
            Vector3 GetCenter(void);

        protected:
        private:
            Vector3 _minVertex;
            Vector3 _maxVertex;
    };
}
#endif /* !BOUNDINGBOX_HPP_ */
