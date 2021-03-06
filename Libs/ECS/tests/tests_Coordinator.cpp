/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** tests_Coordinator
*/

#include <criterion/criterion.h>
#include "AddSystem/AddSystem.hpp"
#include "StorageComponent.hpp"
#include "Coordinator.hpp"

Test(coordinator, coordinator)
{
    ECS::Coordinator coordinator;
    coordinator.AddSystem<AddSystem>();

    ECS::Entity &entity = coordinator.CreateEntity();
    entity.AddComponent<StorageComponent>(3);

    cr_assert_eq(entity.GetComponent<StorageComponent>().value, 3);
    coordinator.Run();
    coordinator.Run();
    coordinator.Run();
    coordinator.Run();
    cr_assert_eq(entity.GetComponent<StorageComponent>().value, 7);
}