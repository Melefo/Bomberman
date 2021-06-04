/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Physics3D
*/

#include "Physics3D.hpp"

namespace RayLib
{

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
        Vector3 botLeftCoords = Vector3(-100.0f, 0.0f, -100.0f);
        Vector3 botRightCoords = Vector3(100.0f, 0.0f, -100.0f);
        Vector3 topRightCoords = Vector3(100.0f, 0.0f, 100.0f);
        Vector3 topLeftCoords = Vector3(-100.0f, 0.0f, 100.0f);

        return(::GetRayCollisionQuad(ray.GetRay(), botLeftCoords.getVector3(), botRightCoords.getVector3(), topRightCoords.getVector3(), topLeftCoords.getVector3()));
        // old
        //return(::GetRayCollisionGround(ray.GetRay(), groundHeight));
    }

    bool Physics3D::CheckCollision(Vector2<float> point, Rectangle rec)
    {
        return (::CheckCollisionPointRec(point.getVector2(), rec.GetRectangle()));
    }
}