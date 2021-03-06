/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Transform
*/

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include <cinttypes>
#include "IComponent.hpp"
#include "Vector3.hpp"

namespace Component
{
    class Transform : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Transform object
             * 
             * @param position 
             * @param rotation 
             * @param scale 
             */
            Transform(RayLib::Vector3 position=RayLib::Vector3(),
                        RayLib::Vector3 rotation=RayLib::Vector3(),
                        RayLib::Vector3 scale=RayLib::Vector3(1.0f, 1.0f, 1.0f));
            /**
             * @brief Destroy the Transform object
             * 
             */
            ~Transform() override = default;
            /**
             * @brief Construct a new Transform object
             * 
             * @param other 
             */
            Transform(const Transform& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return Transform& 
             */
            Transform& operator=(const Transform& other) = default;

            /**
             * @brief Current position in the world
             * 
             */
            RayLib::Vector3 position;
            /**
             * @brief Current rotation
             * 
             */
            RayLib::Vector3 rotation;
            /**
             * @brief Current scale
             * 
             */
            RayLib::Vector3 scale;

            // translate
            // lookat ?
            std::ostream &operator<<(std::ostream &os) override;
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override;

        protected:
        private:
    };
}

#endif /* !TRANSFORM_HPP_ */
