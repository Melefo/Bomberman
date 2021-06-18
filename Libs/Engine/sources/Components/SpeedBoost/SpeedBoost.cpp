/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** SpeedBoost
*/

#include "SpeedBoost.hpp"
#include "AIAlgo.hpp"

namespace Component
{
    SpeedBoost::SpeedBoost(ECS::Entity& attatchedEntity, float pickupRadius) : APickUp(attatchedEntity, pickupRadius)
    {
    }

    void SpeedBoost::OnPickup(ECS::Entity& collision)
    {
        // get AController from collision
        //AController& acontroller = collision.GetComponent<PlayerInputs>();
        if (collision.GetTag() == "Player" && collision.HasComponent<PlayerInputs>()) {
            AController& playerInputs = collision.GetComponent<PlayerInputs>();
            ApplyBoost(playerInputs);
        } else if (collision.GetTag() == "AI" && collision.HasComponent<AIAlgo>()) {
            AController& aiController = collision.GetComponent<AIAlgo>();
            ApplyBoost(aiController);
        }
    }

    void SpeedBoost::ApplyBoost(AController& acontroller)
    {
        // get movement
        Movement& movement = acontroller.GetMovement();

        std::cout << "Applying speed boost" << std::endl;
        // increment speed
        movement.BoostSpeed(0.5f, 5.0f);
        // destroy yourself
        _entity.Dispose();
    }

    void SpeedBoost::LateUpdate(double, ECS::Entity&)
    {

    }
}

