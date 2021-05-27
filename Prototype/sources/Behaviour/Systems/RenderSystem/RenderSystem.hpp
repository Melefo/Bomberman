/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** RenderSystem
*/

#ifndef RENDERSYSTEM_HPP_
#define RENDERSYSTEM_HPP_

#include "ASystem.hpp"
#include "Entity.hpp"

class RenderSystem : public ECS::ASystem {
    public:
        RenderSystem();
        ~RenderSystem() override = default;

        void Update(double dt, ECS::Entity &entity) override;

    protected:
    private:
};

#endif /* !RENDERSYSTEM_HPP_ */
