/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** CoolDownBoost
*/

#include "CoolDownBoost.hpp"

namespace Component
{
    CoolDownBoost::CoolDownBoost(ECS::Entity& entity, float pickUpRadius) : APickUp(entity, pickUpRadius)
    {
    }

    void CoolDownBoost::OnPickup(ECS::Entity& collision)
    {
        // get AController from collision
        //AController& acontroller = collision.GetComponent<PlayerInputs>();
        if (collision.GetTag() == "Player") {
            AController& playerInputs = collision.GetComponent<PlayerInputs>();
            DecrementCooldown(playerInputs);
        }
        // else if tag AI Controller ...

    }

    void CoolDownBoost::DecrementCooldown(AController& acontroller)
    {
        // get movement
        DropBomb& dropBomb = acontroller.GetDropBomb();

        std::cout << "Applying cooldown boost" << std::endl;

        //! soit nombre fixe, soit get delay - 1
        dropBomb.BoostBombCooldown(1, 5.0f);
        _entity.Dispose();
    }

    void CoolDownBoost::LateUpdate(double, ECS::Entity&)
    {

    }
}
