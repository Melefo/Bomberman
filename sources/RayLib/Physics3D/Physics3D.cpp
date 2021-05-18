/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Physics3D
*/

#include "Physics3D.hpp"

namespace RayLib
{
    Physics3D::Physics3D()
    {
    }

    Physics3D::~Physics3D()
    {
    }

    bool Physics3D::CheckCollisionSpheres(Vector3 center1, float radius1, Vector3 center2, float radius2)
    {
        return (::CheckCollisionSpheres(center1, radius1, center2, radius2));
    }

    bool Physics3D::CheckCollisionBoxes(BoundingBox box1, BoundingBox box2)
    {
        return (::CheckCollisionBoxes(box1, box2));
    }

    bool Physics3D::CheckCollisionBoxSphere(BoundingBox box, Vector3 center, float radius)
    {
        return (::CheckCollisionBoxSphere(box, center, radius));
    }

    bool Physics3D::CheckCollisionRaySphere(Ray ray, Vector3 center, float radius)
    {
        return (::CheckCollisionRaySphere(ray, center, radius));
    }

    bool Physics3D::CheckCollisionRaySphereEx(Ray ray, Vector3 center, float radius, Vector3 *collisionPoint)
    {
        return (::CheckCollisionRaySphereEx(ray, center, radius, collisionPoint));
    }

    bool Physics3D::CheckCollisionRayBox(Ray ray, BoundingBox box)
    {
        return (::CheckCollisionRayBox(ray, box));
    }
}