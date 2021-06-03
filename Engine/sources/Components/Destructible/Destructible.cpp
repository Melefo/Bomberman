/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Destructible
*/

#include "Destructible.hpp"

namespace Component
{
    Destructible::Destructible(ECS::Entity& entity, int resistance) : _myEntity(entity), _resistance(resistance)
    {
    }

    int Destructible::GetResistance()
    {
        return (_resistance);
    }

    void Destructible::TakeDamage(int damage)
    {
        _resistance -= damage;

        if (_resistance <= 0) {
            _resistance = 0;
            _myEntity.Dispose();
        }
    }
}
