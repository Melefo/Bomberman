/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Vector4
*/

#ifndef VECTOR4_HPP_
#define VECTOR4_HPP_

#include <raylib.h>

namespace RayLib
{
    /**
     * @brief Vector4 encapsulation
     * 
     */
    class Vector4 {
        public:
            /**
             * @brief Construct a new Vector 4
             * Initialize values to zero
             */
            Vector4();

            /**
             * @brief Construct a new Vector 4 object
             * 
             * @param x initialize x parameter
             */
            Vector4(float x);

            /**
             * @brief Construct a new Vector 4 object
             * 
             * @param x initialize x parameter
             * @param y initialize y parameter
             */
            Vector4(float x, float y);

            /**
             * @brief Construct a new Vector 4 object
             * 
             * @param x initialize x parameter
             * @param y initialize y parameter
             * @param z initialize z parameter
             */
            Vector4(float x, float y, float z);

            /**
             * @brief Construct a new Vector 4 object
             * 
             * @param x initialize x parameter
             * @param y initialize y parameter
             * @param z initialize z parameter
             * @param w initialize w parameter
             */
            Vector4(float x, float y, float z, float w);

            /**
             * @brief Construct a new Vector 4 object
             * 
             * @param vec 
             */
            Vector4(const Vector4 &vec);

            /**
             * @brief Construct a new Vector 4 object
             * 
             * @param vec 
             */
            Vector4(const ::Vector4 &vec);

            ~Vector4() = default;

            /**
             * @brief Get the Vector4 as a raylib structure
             * 
             * @return ::Vector4
             */
            ::Vector4 getVector4(void);

            /**
             * @brief Assignment operator
             * 
             * @param vector4
             * @return Vector4& 
             */
            Vector4 &operator=(const Vector4& vector4);

            float x;
            float y;
            float z;
            float w;
        protected:
        private:
    };
}

#endif /* !VECTOR4_HPP_ */
