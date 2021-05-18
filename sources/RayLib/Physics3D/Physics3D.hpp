/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Physics3D
*/

#ifndef PHYSICS3D_HPP_
#define PHYSICS3D_HPP_

#include <raylib.h>

namespace RayLib
{
    class Physics3D {
        public:
            Physics3D();
            ~Physics3D();

            static bool CheckCollisionSpheres(Vector3 center1, float radius1, Vector3 center2, float radius2);        // Detect collision between two spheres
            static bool CheckCollisionBoxes(BoundingBox box1, BoundingBox box2);                                      // Detect collision between two bounding boxes
            static bool CheckCollisionBoxSphere(BoundingBox box, Vector3 center, float radius);                       // Detect collision between box and sphere
            static bool CheckCollisionRaySphere(Ray ray, Vector3 center, float radius);                               // Detect collision between ray and sphere
            static bool CheckCollisionRaySphereEx(Ray ray, Vector3 center, float radius, Vector3 *collisionPoint);    // Detect collision between ray and sphere, returns collision point
            static bool CheckCollisionRayBox(Ray ray, BoundingBox box);                                               // Detect collision between ray and box

        protected:
        private:
    };
}

#endif /* !PHYSICS3D_HPP_ */
