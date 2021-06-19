/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PhysicsBody
*/

#ifndef PHYSICSBODY_HPP_
#define PHYSICSBODY_HPP_

#include <cinttypes>
#include "IComponent.hpp"
#include "Vector3.hpp"
#include "PhysicsBody.hpp"

namespace Component
{
    /**
     * @brief Physicsbody class (CF Unity's rigidbody)
     * 
     */
    class PhysicsBody : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Physics Body object
             * 
             * @param velocity 
             */
            PhysicsBody();

            /**
             * @brief Destroy the Physics Body object
             * 
             */
            ~PhysicsBody() override = default;
            /**
             * @brief Construct a new Physics Body object
             * 
             * @param other 
             */
            PhysicsBody(const PhysicsBody& other) = default;
            /**
             * @brief Assignment operator
             * 
             * @param other 
             * @return PhysicsBody& 
             */
            PhysicsBody& operator=(const PhysicsBody& other) = default;

            std::ostream &operator<<(std::ostream &os) override {return os;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

            /**
             * @brief Ultimately used to change the entity's position
             * 
             */
            RayLib::Vector3 velocity;
        protected:
        private:
    };
}

#endif /* !PHYSICSBODY_HPP_ */
