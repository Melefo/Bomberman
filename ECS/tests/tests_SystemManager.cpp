/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** tests_SystemManager
*/

#include <criterion/criterion.h>
#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "AddSystem/AddSystem.hpp"
#include "StorageComponent/StorageComponent.hpp"

Test(AddSystem, test)
{
    ECS::SystemManager sysmanager;
    ECS::EntityManager entmanager;

    ECS::Entity &entity = entmanager.CreateEntity();
    entity.AddComponent<StorageComponent>();
    AddSystem &system = sysmanager.AddSystem<AddSystem>();

    cr_assert_eq(entity.GetComponent<StorageComponent>().value, 0);
    system.Update(0, entity);
    cr_assert_eq(entity.GetComponent<StorageComponent>().value, 1);
}