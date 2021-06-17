/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Physics2D
*/

#ifndef PHYSICS2D_HPP_
#define PHYSICS2D_HPP_

#include <physac.h>
#include <raylib.h>
#include "PhysicsBody.hpp"

namespace RayLib
{
    class Physics2D {
        public:
            Physics2D() = default;
            ~Physics2D() = default;

            static bool CheckCollision(RayLib::PhysicsBody& body1, RayLib::PhysicsBody& body2);

            static void InitPhysics(void);
            static void ClosePhysics(void);

        protected:
        private:
    };
}

#endif /* !PHYSICS2D_HPP_ */
