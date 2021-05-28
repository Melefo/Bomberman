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
    class BoundingBox {
        public:
            BoundingBox(Vector3 minVert, Vector3 maxVert);
            BoundingBox(const BoundingBox& other);
            ~BoundingBox();

            void InitFromCube(Vector3 cubePos, Vector3 cubeScale);

            BoundingBox& operator=(const BoundingBox& other);

            ::BoundingBox GetBounds(void);
            Vector3 GetCenter(void);

        protected:
        private:
            Vector3 _minVertex;
            Vector3 _maxVertex;
    };
}
#endif /* !BOUNDINGBOX_HPP_ */
