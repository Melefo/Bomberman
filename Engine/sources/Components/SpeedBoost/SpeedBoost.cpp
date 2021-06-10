/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** SpeedBoost
*/

#include "SpeedBoost.hpp"

namespace Component
{
    SpeedBoost::SpeedBoost(ECS::Entity& attatchedEntity) : APickUp(attatchedEntity)
    {
    }

    void SpeedBoost::OnPickup(ECS::Entity& collision)
    {
        // get AController from collision
        //AController& acontroller = collision.GetComponent<PlayerInputs>();
        if (collision.GetTag() == "Player") {
            AController& playerInputs = collision.GetComponent<PlayerInputs>();
            ApplyBoost(playerInputs);
        }
        // else if tag AI Controller ...

    }

    void SpeedBoost::ApplyBoost(AController& acontroller)
    {
        // get movement
        Movement& movement = acontroller.GetMovement();

        std::cout << "Applying speed boost" << std::endl;
        // increment speed
        // destroy yourself
        //! (decrement speed in movement class)
    }

    void SpeedBoost::Update(double, ECS::Entity&)
    {

    }
}

