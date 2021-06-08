/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** OjectComponent
*/

#ifndef OJECTCOMPONENT_HPP_
#define OJECTCOMPONENT_HPP_

#include <cinttypes>
#include "IComponent.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Vector3.hpp"

class ObjectComponent : public ECS::IComponent
{
    public:
        ObjectComponent();
        ~ObjectComponent() override = default;

        RayLib::Model model;
        RayLib::Texture texture;
        RayLib::Vector3 position;
        float size;

        std::ostream& operator<<(std::ostream& stream) override;

    protected:
    private:
};

#endif /* !OJECTCOMPONENT_HPP_ */
