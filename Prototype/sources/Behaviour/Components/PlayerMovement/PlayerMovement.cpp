/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** PlayerMovement
*/

#include "PlayerMovement.hpp"
#include <iostream>

namespace Prototype
{
    PlayerMovement::PlayerMovement(ECS::Entity& attatchedEntity, float moveSpeed) :
    _input(), _entity(attatchedEntity), _myPhysicsBody(_entity.GetComponent<PhysicsBody>())
    {
        _speed = moveSpeed;
    }

    void PlayerMovement::Update(float dt)
    {
        (void) dt;
        // idéalement ce serait += mais comme on a pas de drag, on ne ferait qu'accélérer
        _myPhysicsBody.velocity = RayLib::Vector3(_input.GetHorizontalAxis(),
                                                  0.0f,
                                                  _input.GetVerticalAxis()) * _speed;
    }
}
