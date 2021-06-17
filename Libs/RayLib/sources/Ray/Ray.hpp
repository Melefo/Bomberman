/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Ray
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include "Vector3.hpp"

namespace RayLib
{
    /**
     * @brief Ray encapsulation
     * 
     */
    class Ray {
        public:
            /**
             * @brief Construct a new Ray object
             * Sets position and direction to 0.0
             */
            Ray();

            /**
             * @brief Construct a new Ray object
             * 
             * @param position 
             * @param direction 
             */
            Ray(Vector3 position, Vector3 direction);

            /**
             * @brief Construct a new Ray object
             * 
             * @param other 
             */
            Ray(const Ray& other);

            /**
             * @brief Construct a new Ray object
             * 
             * @param other 
             */
            Ray(const ::Ray& other);

            /**
             * @brief assignment operator
             * 
             * @param other 
             * @return Ray& 
             */
            Ray& operator=(const Ray& other);

            /**
             * @brief Destroy the Ray object
             * 
             */
            ~Ray() = default;

            /**
             * @brief Get ray's starting position
             * 
             * @return Vector3& 
             */
            Vector3& GetPosition(void);

            /**
             * @brief Get the ray's direction
             * 
             * @return Vector3& 
             */
            Vector3& GetDirection(void);

            /**
             * @brief Get the Ray as a raylib structure
             * 
             * @return ::Ray 
             */
            ::Ray GetRay();

        protected:
        private:
            Vector3 _position;
            Vector3 _direction;
    };
}

#endif /* !RAY_HPP_ */