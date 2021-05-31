/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Vector3
*/

#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <raylib.h>

namespace RayLib
{
    class Vector3
    {
        public:
            Vector3();
            Vector3(float x);
            Vector3(float x, float y);
            Vector3(float x, float y, float z);
            Vector3(const Vector3 &vec);
            Vector3(const ::Vector3 &vec);

            ~Vector3();

            ::Vector3 getVector3(void);

            Vector3 &operator=(const Vector3& vector3);
            Vector3 &operator*=(const float factor);
            Vector3 &operator+=(const Vector3& vector3);

            Vector3 operator+(const Vector3& vec);
            Vector3 operator-(const Vector3& vec);
            Vector3 operator*(const Vector3& vec);
            Vector3 operator*(const float factor);


            float x;
            float y;
            float z;
        protected:
        private:
    };
}

#endif /* !VECTOR3_HPP_ */
