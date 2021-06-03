/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** main
*/

#include <iostream>
#include "Coordinator.hpp"
#include "Transform.hpp"
#include "PhysicsSystem.hpp"
#include "RenderSystem.hpp"
#include "BehaviourSystem.hpp"
#include "UISystem.hpp"
#include "CollisionSystem.hpp"
#include "BoxCollider.hpp"
#include "PlayerMovement.hpp"
#include "DropBomb.hpp"
#include "Button.hpp"
#include "ButtonCallbacks.hpp"
#include "Draggable.hpp"

ECS::Entity& InitCat(ECS::Coordinator& coordinator)
{
    // cat
    ECS::Entity &entity = coordinator.CreateEntity();
    entity.AddComponent<Component::Transform>();
    entity.AddComponent<Component::PhysicsBody>();
    entity.AddComponent<Component::Renderer>("../assets/Cat_V2/cat.obj", "../assets/models/cube/def_text.png");
    entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));
    entity.AddComponent<Component::IBehaviour, Component::PlayerMovement>(entity, 0.5f);
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(0.025f, 0.025f, 0.025f);

    entity.AddComponent<Component::IBehaviour, Component::DropBomb>(entity, coordinator);

    //entity.AddComponent<Prototype::Destructible>(entity, 1);

    return (entity);
}

ECS::Entity& InitButton(ECS::Coordinator& coordinator)
{
    ECS::Entity &entity = coordinator.CreateEntity();
    entity.AddComponent<Component::IUIObject, Component::Button>();
    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 20.0f, 0.0f), 0.0f, RayLib::Vector3(100.0f, 50.0f, 1.0f));
    entity.AddComponent<Component::IBehaviour, Component::ButtonCallbacks>(entity);

    return (entity);
}

ECS::Entity& InitBox(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    ECS::Entity& entity = coordinator.CreateEntity();
    entity.AddComponent<Component::Transform>();
    //entity.AddComponent<Prototype::PhysicsBody>();
    entity.AddComponent<Component::Renderer>();
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(10.0f, 10.0f, 10.0f);
    entity.GetComponent<Component::Transform>().position = RayLib::Vector3(-20.0f, 0.0f, 0.0f);

    entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));

    entity.AddComponent<Component::IBehaviour, Component::Draggable>(entity, camera);

    entity.AddComponent<Component::Destructible>(entity, 1);

    return (entity);
}

int main(void)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");
    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 20.0f, -50.0f), RayLib::Vector3(0.0f, 10.0f, 0.0f));

    /*ECS::Entity& cat = */InitCat(*coordinator.get());
    /*ECS::Entity& button = */InitButton(*coordinator.get());
    /*ECS::Entity& box = */InitBox(*coordinator.get(), camera);

    coordinator->AddSystem<Component::PhysicsSystem>();
    coordinator->AddSystem<Component::RenderSystem>();
    coordinator->AddSystem<Component::BehaviourSystem>();
    coordinator->AddSystem<Component::UISystem>(camera);

    window->SetTargetFPS(60);
    camera.SetCameraMode(CAMERA_FREE);

    while (!window->WindowShouldClose())
    {
        camera.Update();

        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);
        camera.BeginMode();

        coordinator->Run();

        window->DrawGrid(20, 10.0f);
        camera.EndMode();
        window->EndDrawing();
    }
    return (0);
}