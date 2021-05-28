/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Explosion
*/

#include "Explosion.hpp"

namespace Prototype
{
    Explosion::Explosion(RayLib::Vector3 startRadius, Explosion::ExplosionType startType, unsigned int startPower)
    {
        radius = startRadius;
        type = startType;
        power = startPower;
    }
}