/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Physics3D
*/

#ifndef PHYSICS3D_HPP_
#define PHYSICS3D_HPP_

#include <raylib.h>
#include "Ray.hpp"
#include "Vector3.hpp"
#include "BoundingBox.hpp"
#include "Rectangle.hpp"
#include "Vector2.hpp"
#include "RayCollision.hpp"

namespace RayLib
{
    class Physics3D {
        public:
            Physics3D();
            ~Physics3D();

            static bool CheckCollision(Vector3 center1, float radius1, Vector3 center2, float radius2);        // Detect collision between two spheres
            static bool CheckCollision(BoundingBox box1, BoundingBox box2);                                      // Detect collision between two bounding boxes
            static bool CheckCollision(BoundingBox box, Vector3 center, float radius);                       // Detect collision between box and sphere
            static RayCollision CheckCollision(Ray ray, Vector3 center, float radius);                               // Detect collision between ray and sphere
            static RayCollision CheckCollision(Ray ray, BoundingBox box);                                               // Detect collision between ray and box
            static RayCollision CheckCollision(Ray ray, float groundHeight);


        protected:
        private:
    };
}

#endif /* !PHYSICS3D_HPP_ */
