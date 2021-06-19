/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RangeBoost
*/

#include "RangeBoost.hpp"
#include "AIAlgo.hpp"
#include "EntityFactory.hpp"

namespace Component
{
    RangeBoost::RangeBoost(ECS::Entity& entity, float pickUpRadius): APickUp(entity, pickUpRadius)
    {
    }

    void RangeBoost::OnPickup(ECS::Entity& collision)
    {
        // get AController from collision
        //AController& acontroller = collision.GetComponent<PlayerInputs>();
        if (collision.GetTag().find("PlayerEntity") != std::string::npos) {
            AController& playerInputs = collision.GetComponent<PlayerInputs>();
            IncrementRange(playerInputs);
            EntityFactory entityFactory(_coordinator);
            Component::AController &controller = collision.GetComponent<Component::PlayerInputs>().GetAController();
            entityFactory.createHUDBonusIcon(controller, getPlayerNbr(collision.GetTag()), "../assets/PickUps/RangePickUp_texture.png", controller.GetDropBomb().GetBonusTime());
        } else if (collision.GetTag().find("AI") != std::string::npos) {
            AController& aiController = collision.GetComponent<AIAlgo>();
            IncrementRange(aiController);
        }
    }

    void RangeBoost::IncrementRange(AController& acontroller)
    {
        // get movement
        DropBomb& dropBomb = acontroller.GetDropBomb();

        //std::cout << "Applying Range boost" << std::endl;

        //! soit nombre fixe, soit get number + 1
        dropBomb.BoostBombNumber(3, 10.0f);
        _entity.Dispose();
    }

    void RangeBoost::LateUpdate(double, ECS::Entity&)
    {

    }
}