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

    bool Physics3D::CheckCollision(Vector3 center1, float radius1, Vector3 center2, float radius2)
    {
        return (::CheckCollisionSpheres(center1.getVector3(),
                                        radius1,
                                        center2.getVector3(),
                                        radius2));
    }

    bool Physics3D::CheckCollision(BoundingBox box1, BoundingBox box2)
    {
        return (::CheckCollisionBoxes(box1.GetBounds(), box2.GetBounds()));
    }

    bool Physics3D::CheckCollision(BoundingBox box, Vector3 center, float radius)
    {
        return (::CheckCollisionBoxSphere(box.GetBounds(), center.getVector3(), radius));
    }

    RayCollision Physics3D::CheckCollision(Ray ray, Vector3 center, float radius)
    {
        return (::GetRayCollisionSphere(ray.GetRay(), center.getVector3(), radius));
    }

    RayCollision Physics3D::CheckCollision(Ray ray, BoundingBox box)
    {
        return (::GetRayCollisionBox(ray.GetRay(), box.GetBounds()));
    }

    RayCollision Physics3D::CheckCollision(Ray ray, float groundHeight)
    {
        return(::GetRayCollisionGround(ray.GetRay(), groundHeight));
    }

}