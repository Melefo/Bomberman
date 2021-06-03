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
    /**
     * @brief Physics3D static encapsulation
     * 
     */
    class Physics3D {
        public:
            /**
             * @brief Construct a new Physics3D object
             * 
             */
            Physics3D() = default;
            /**
             * @brief Destroy the Physics3D object
             * 
             */
            ~Physics3D() = default;

            /**
             * @brief Detect collision between two spheres
             * 
             * @param center1 
             * @param radius1 
             * @param center2 
             * @param radius2 
             * @return true 
             * @return false 
             */
            static bool CheckCollision(Vector3 center1, float radius1, Vector3 center2, float radius2);

            /**
             * @brief Detect collision between two bounding boxes
             * 
             * @param box1 
             * @param box2 
             * @return true 
             * @return false 
             */
            static bool CheckCollision(BoundingBox box1, BoundingBox box2);

            /**
             * @brief Detect collision between box and sphere
             * 
             * @param box 
             * @param center 
             * @param radius 
             * @return true 
             * @return false 
             */
            static bool CheckCollision(BoundingBox box, Vector3 center, float radius);

            /**
             * @brief Detect collision between ray and sphere
             * 
             * @param ray 
             * @param center 
             * @param radius 
             * @return RayCollision 
             */
            static RayCollision CheckCollision(Ray ray, Vector3 center, float radius);

            /**
             * @brief Detect collision between ray and box
             * 
             * @param ray 
             * @param box 
             * @return RayCollision 
             */
            static RayCollision CheckCollision(Ray ray, BoundingBox box);

            /**
             * @brief Raycast to floor
             * 
             * @param ray 
             * @param groundHeight 
             * @return RayCollision 
             */
            static RayCollision CheckCollision(Ray ray, float groundHeight);

            /**
             * @brief Detect collision between point and rectangle
             * Useful for UI
             * @param point 
             * @param rec 
             * @return true 
             * @return false 
             */
            static bool CheckCollision(Vector2<float> point, Rectangle rec);


        protected:
        private:
    };
}

#endif /* !PHYSICS3D_HPP_ */
