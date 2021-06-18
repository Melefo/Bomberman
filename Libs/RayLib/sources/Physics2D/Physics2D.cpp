/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Physics2D
*/

#include "Physics2D.hpp"

namespace RayLib
{
    /*bool Physics2D::CheckCollision(RayLib::PhysacBody& body1, RayLib::PhysacBody& body2)
    {
        bool colliding = false;

        // create manifold
        // ! ceci est un raw ptr !
        ::PhysicsManifold manifold = ::CreatePhysicsManifold(&body1.GetPhysicsBody(), &body2.GetPhysicsBody());
        // solve collisions
        ::SolvePhysicsManifold(manifold);
        colliding = manifold->contactsCount > 0;

        PHYSAC_FREE(manifold);
        return (colliding);
    }*/


    bool Physics2D::CheckCollision(const Rectangle& rec1, const Rectangle& rec2)
    {
        return (::CheckCollisionRecs(rec1, rec2));
    }

    bool Physics2D::CheckCollision(const Circle& circle1, const Circle& circle2)
    {
        return (::CheckCollisionCircles(circle1.GetCenter().getVector2(),
                                        circle1.GetRadius(),
                                        circle2.GetCenter().getVector2(),
                                        circle2.GetRadius()));
    }

    bool Physics2D::CheckCollision(const Rectangle& rec, const Circle& circle)
    {
        return (::CheckCollisionCircleRec(circle.GetCenter().getVector2(),
                                          circle.GetRadius(),
                                          rec));
    }

    bool Physics2D::CheckCollision(RayLib::Vector2<float> point, const Rectangle& rec)
    {
        return (::CheckCollisionPointRec(point.getVector2(), rec));
    }

}

