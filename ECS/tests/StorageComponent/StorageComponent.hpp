/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** StorageComponent
*/

#ifndef STORAGECOMPONENT_HPP_
#define STORAGECOMPONENT_HPP_

#include "IComponent.hpp"

class StorageComponent : public ECS::IComponent
{
    public:
        StorageComponent() = default;
        ~StorageComponent() override = default;
        int value = 0;
};

#endif /* !STORAGECOMPONENT_HPP_ */
