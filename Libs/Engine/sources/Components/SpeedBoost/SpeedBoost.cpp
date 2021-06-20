/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** SpeedBoost
*/

#include "SpeedBoost.hpp"
#include "AIAlgo.hpp"
#include "EntityFactory.hpp"

namespace Component
{
    SpeedBoost::SpeedBoost(ECS::Entity& attatchedEntity, float pickupRadius) : APickUp(attatchedEntity, pickupRadius)
    {
    }

    void SpeedBoost::OnPickup(ECS::Entity& collision)
    {
        if (collision.GetTag().find("PlayerEntity") != std::string::npos) {
            AController& controller = collision.GetComponent<PlayerInputs>();
            if (controller.GetMovement().GetBonusTime() > 0.0) {
                ApplyBoost(controller);
                return;
            }
            ApplyBoost(controller);

            EntityFactory entityFactory(*ECS::Coordinator::GetInstance());
            entityFactory.createHUDBonusIcon(controller, getPlayerNbr(collision.GetTag()), "../assets/PickUps/SpeedPickUp_texture.png", controller.GetMovement().GetBonusTime());
            entityFactory.createHUDBonusBar(controller, getPlayerNbr(collision.GetTag()), "SpeedBoost", controller.GetMovement().GetBonusTime());

        } else if (collision.GetTag().find("AI") != std::string::npos) {
            AController& aiController = collision.GetComponent<AIAlgo>();
            ApplyBoost(aiController);
        }
    }

    void SpeedBoost::ApplyBoost(AController& acontroller)
    {
        // get movement
        Movement& movement = acontroller.GetMovement();

        //std::cout << "Applying speed boost" << std::endl;
        // increment speed
        movement.BoostSpeed(0.5f, 5.0f);
        // destroy yourself
        _entity.Dispose();
    }

    void SpeedBoost::LateUpdate(double, ECS::Entity&)
    {

    }
}

