/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Vector3
*/

#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <raylib.h>
#include "IXMLSerializable.hpp"
#include <cmath>
#include <sstream>

namespace RayLib
{
    /**
     * @brief Vector3 encapsulation
     * 
     */
    class Vector3 : public IXMLSerializable
    {
        public:
            /**
             * @brief Construct a new Vector 3
             * Initialize values to zero
             */
            Vector3();

            /**
             * @brief Construct a new Vector 3 object
             * 
             * @param x initialize x parameter
             */
            Vector3(float x);

            /**
             * @brief Construct a new Vector 3 object
             * 
             * @param x initialize x parameter
             * @param y initialize y parameter
             */
            Vector3(float x, float y);

            /**
             * @brief Construct a new Vector 3 object
             * 
             * @param x initialize x parameter
             * @param y initialize y parameter
             * @param z initialize z parameter
             */
            Vector3(float x, float y, float z);

            /**
             * @brief Construct a new Vector 3 object
             * 
             * @param vec 
             */
            Vector3(const Vector3 &vec);

            /**
             * @brief Construct a new Vector 3 object
             * 
             * @param vec 
             */
            Vector3(const ::Vector3 &vec);

            ~Vector3() = default;

            /**
             * @brief Get the Vector3 as a raylib structure
             * 
             * @return ::Vector3
             */
            ::Vector3 getVector3(void);

            /**
             * @brief Assignment operator
             * 
             * @param vector3 
             * @return Vector3& 
             */
            Vector3 &operator=(const Vector3& vector3);

            /**
             * @brief Multiply vector by factor
             * 
             * @param factor 
             * @return Vector3& 
             */
            Vector3 &operator*=(const float factor);

            /**
             * @brief Add two vectors
             * 
             * @param vector3 
             * @return Vector3& 
             */
            Vector3 &operator+=(const Vector3& vector3);

            /**
             * @brief Add two vectors
             * 
             * @param vec 
             * @return Vector3 
             */
            Vector3 operator+(const Vector3& vec);

            /**
             * @brief Subtract vector
             * 
             * @param vec 
             * @return Vector3 
             */
            Vector3 operator-(const Vector3& vec);

            /**
             * @brief Multiply each parameter by other corresponding parameters
             * 
             * @param vec 
             * @return Vector3 
             */
            Vector3 operator*(const Vector3& vec);

            /**
             * @brief Multiply vector parameters by factor
             * 
             * @param factor 
             * @return Vector3 
             */
            Vector3 operator*(const float factor);

            /**
             * @brief Return the distance to other vector
             * 
             * @param other 
             * @return float 
             */
            float Distance(const Vector3 other);

            /**
             * @brief Smoothly modify values to match target
             * 
             * @param target 
             * @param smoothTime 
             * @param deltaTime 
             */
            void SmoothDamp(Vector3 target, float smoothTime, float deltaTime);

            /**
             * @brief Linearly interpolate vector3 to target by t
             * 
             * @param target 
             * @param t 
             */
            void Lerp(Vector3 target, float t);

            bool operator==(const RayLib::Vector3& other);

            void LoadFromXML(std::istream &is) override;
            void SerializeToXML(std::ostream &os) const override;

            float x;
            float y;
            float z;
        protected:
        private:
    };

}
/*
inline std::ostream& operator<<(std::ostream &os, const RayLib::Vector3& xml)
{
    os << "<Vector3>" << std::endl;
    os << "\t<x>" << xml.x << "</x>" << std::endl;
    os << "\t<y>" << xml.y << "</y>" << std::endl;
    os << "\t<z>" << xml.z << "</z>" << std::endl;
    os << "</Vector3>" << std::endl;
    return os;
}

inline std::istream& operator>>(std::istream &is, RayLib::Vector3& xml)
{
    boost::property_tree::ptree tree;
    boost::property_tree::xml_parser::read_xml(is, tree);

    boost::property_tree::ptree vec3 = tree.get_child("Vector3");

    xml.x = vec3.get<float>("x");
    xml.y = vec3.get<float>("y");
    xml.z = vec3.get<float>("z");
    return is;
}
*/

#endif /* !VECTOR3_HPP_ */
