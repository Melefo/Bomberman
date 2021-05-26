/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** MoveSystem
*/

#ifndef MOVESYSTEM_HPP_
#define MOVESYSTEM_HPP_

#include "ASystem.hpp"
#include "Entity.hpp"

class MoveSystem : public ECS::ASystem
{
    public:
        MoveSystem();
        ~MoveSystem() override = default;

        void Update(double dt, ECS::Entity &entity) override;
    protected:
    private:
};

#endif /* !MOVESYSTEM_HPP_ */
