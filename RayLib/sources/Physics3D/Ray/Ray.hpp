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
    class Ray {
        public:
            Ray();
            Ray(Vector3 position, Vector3 direction);
            Ray(const Ray& other);
            Ray(const ::Ray& other);

            Ray& operator=(const Ray& other);
            ~Ray();

            Vector3& GetPosition(void);
            Vector3& GetDirection(void);

            ::Ray GetRay();

        protected:
        private:
            Vector3 _position;
            Vector3 _direction;
    };
}

#endif /* !RAY_HPP_ */
