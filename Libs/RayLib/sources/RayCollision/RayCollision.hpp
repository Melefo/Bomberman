/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RayCollision
*/

#ifndef RAYCOLLISION_HPP_
#define RAYCOLLISION_HPP_

#include "Vector3.hpp"
#include "raylib.h"

namespace RayLib
{
    /**
     * @brief RayCollision encapsulation
     * 
     */
    class RayCollision {
        public:
            /**
             * @brief Construct a new Ray Collision object
             * Initializes values to zero and hit to false
             */
            RayCollision();

            /**
             * @brief Destroy the Ray Collision object
             * 
             */
            ~RayCollision() = default;

            /**
             * @brief Construct a new Ray Collision object
             * 
             * @param other 
             */
            RayCollision(const RayCollision& other);

            /**
             * @brief Construct a new Ray Collision object
             * 
             * @param other 
             */
            RayCollision(const ::RayCollision& other);

            /**
             * @brief 
             * 
             * @param other 
             * @return RayCollision& 
             */
            RayCollision& operator=(const RayCollision& other);

            /**
             * @brief 
             * 
             * @param other 
             * @return RayCollision& 
             */
            RayCollision& operator=(const ::RayCollision& other);

            /**
             * @brief Get the Hit Info as a raylib structure
             * 
             * @return ::RayCollision 
             */
            ::RayCollision GetHitInfo(void);

            /**
             * @brief returns hit value of structure
             * 
             * @return true 
             * @return false 
             */
            bool HasHit(void);

            /**
             * @brief Get the Distance to collision object
             * 
             * @return float 
             */
            float GetDistance(void);

            /**
             * @brief Get the position of collision
             * 
             * @return Vector3& 
             */
            Vector3& GetPosition(void);

            /**
             * @brief Get the surface normal
             * 
             * @return Vector3& 
             */
            Vector3& GetNormal(void);

        protected:
        private:
            bool _hit;               // Did the ray hit something?
            float _distance;         // Distance to nearest hit
            Vector3 _point;       // Position of nearest hit
            Vector3 _normal;         // Surface normal of hit
    };
}

#endif /* !RAYCOLLISION_HPP_ */