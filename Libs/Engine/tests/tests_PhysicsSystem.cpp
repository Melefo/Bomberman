/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** tests_PhysicsSystem
*/

#include <criterion/criterion.h>
#include "PhysicsSystem.hpp"
#include "Coordinator.hpp"
#include "Transform.hpp"
#include <iostream>

Test(PhysicsSystem, velocity)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
    Component::PhysicsSystem& physicsSystem = coordinator->AddSystem<Component::PhysicsSystem>();

    ECS::Entity &entity = coordinator->CreateEntity();
    entity.AddComponent<Component::Transform>(RayLib::Vector3(5.0f, 0.0f, 0.0f));
    entity.AddComponent<Component::PhysicsBody>();

    Component::PhysicsBody& physicsBody = entity.GetComponent<Component::PhysicsBody>();
    Component::Transform& transform = entity.GetComponent<Component::Transform>();
    physicsBody.velocity = RayLib::Vector3(1.0f, 0.0f, 0.0f);

    physicsSystem.FixedUpdate(entity);

    // position + velocity
    cr_assert_eq(transform.position.x, 6.0f);
}