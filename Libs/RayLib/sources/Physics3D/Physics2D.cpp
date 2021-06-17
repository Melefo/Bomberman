/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Physics2D
*/

#include "Physics2D.hpp"

namespace RayLib
{
    bool Physics2D::CheckCollision(RayLib::PhysicsBody& body1, RayLib::PhysicsBody& body2)
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
    }

    void InitPhysics(void)
    {
        ::InitPhysics();
    }

    void ClosePhysics(void)
    {
        ::ClosePhysics();
    }


}

