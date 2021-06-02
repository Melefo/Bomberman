/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** tests_EntityManager
*/

#include <criterion/criterion.h>
#include <memory>
#include "EntityManager.hpp"
#include "Entity.hpp"

Test(createEntity, created)
{
    ECS::EntityManager manager;

    ECS::Entity &entity = manager.CreateEntity();
    cr_assert_eq(entity.GetId(), 1);
}

Test(deleteEntity, deleted)
{
    ECS::EntityManager manager;

    ECS::Entity &entity = manager.CreateEntity();
    ECS::Entity &entity2 = manager.CreateEntity();

    cr_assert_eq(entity.GetId(), 1);
    cr_assert_eq(entity2.GetId(), 2);
    
    entity.Dispose();

    ECS::Entity &entity3 = manager.CreateEntity();
    cr_assert_eq(entity3.GetId(), 1);
}