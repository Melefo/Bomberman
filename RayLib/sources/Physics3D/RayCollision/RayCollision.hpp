/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RayCollision
*/

#ifndef RAYCOLLISION_HPP_
#define RAYCOLLISION_HPP_

#include "Vector3.hpp"

namespace RayLib
{
    class RayCollision {
        public:
            RayCollision();
            ~RayCollision();

            RayCollision(const RayCollision& other);
            RayCollision(const ::RayCollision& other);

            RayCollision& operator=(const RayCollision& other);
            RayCollision& operator=(const ::RayCollision& other);

            ::RayCollision GetHitInfo(void);

            bool HasHit(void);
            float GetDistance(void);
            Vector3& GetPosition(void);
            Vector3& GetNormal(void);

        protected:
        private:
            // privé ou public ?
            bool _hit;               // Did the ray hit something?
            float _distance;         // Distance to nearest hit
            Vector3 _point;       // Position of nearest hit
            Vector3 _normal;         // Surface normal of hit
    };
}

#endif /* !RAYCOLLISION_HPP_ */
