/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** tests_XML
*/

#include <criterion/criterion.h>
#include "XML.hpp"
#include "Transform.hpp"
#include "Coordinator.hpp"

Test(load, invalid)
{
    ECS::Coordinator coordinator;

    cr_assert_throw(XML::LoadMap("doesntexists", coordinator), XMLException);
}

Test(load, loaded)
{
    ECS::Coordinator coordinator;

    cr_assert_no_throw(XML::LoadMap("../Engine/tests/map.xml", coordinator));

    auto &list = coordinator.GetEntities();
    cr_assert_eq(list.size(), 5);
    for (auto &entity : list)
        if (!entity->HasComponent<Component::Transform>())
            cr_assert_fail();
}