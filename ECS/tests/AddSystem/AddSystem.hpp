/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** AddSystem
*/

#ifndef ADDSYSTEM_HPP_
#define ADDSYSTEM_HPP_

#include <string>
#include <vector>
#include "Entity.hpp"
#include "ASystem.hpp"
#include "../StorageComponent/StorageComponent.hpp"

class AddSystem : public ECS::ASystem
{
    private:
    public:
        AddSystem();
        ~AddSystem() override = default;

        void Update(double dt, ECS::Entity &entity) override;

};

#endif /* !ADDSYSTEM_HPP_ */
