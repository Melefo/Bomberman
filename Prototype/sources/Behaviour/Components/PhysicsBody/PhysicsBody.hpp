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

class PhysicsBody : public ECS::IComponent {
    public:
        PhysicsBody(RayLib::Vector3 velocity);
        ~PhysicsBody() override = default;

        RayLib::Vector3 velocity;
    protected:
    private:
};

#endif /* !PHYSICSBODY_HPP_ */
