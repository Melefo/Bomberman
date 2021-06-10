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
#include "Input.hpp"
#include "Camera.hpp"
#include "SphereCollider.hpp"
#include "GameConfigurator.hpp"
#include "Scenes.hpp"

#include "TerrainGenerator.hpp"

#define BOX_SIZE 10


ECS::Entity& InitCat(ECS::Coordinator& coordinator)
{
    // cat
    ECS::Entity &entity = coordinator.CreateEntity();
    entity.AddComponent<Component::Transform>(RayLib::Vector3(30, 0, 30));
    entity.AddComponent<Component::PhysicsBody>();
    entity.AddComponent<Component::Renderer>("../assets/BoxMan/guy.iqm", "../assets/BoxMan/guytex.png");
    entity.AddComponent<Component::Animator>("../assets/BoxMan/guyanim.iqm", "Idle");
    //entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));
    entity.AddComponent<Component::Collider, Component::SphereCollider>(entity, RayLib::Vector3(), 4.0f);

    entity.AddComponent<Component::IBehaviour, Component::PlayerMovement>(entity, 0.5f, RayLib::Input(RayLib::Vector2<int>(KEY_RIGHT, KEY_LEFT),
                                                                                                      RayLib::Vector2<int>(KEY_DOWN, KEY_UP)));

    entity.GetComponent<Component::Transform>().rotation = RayLib::Vector3(-90.0f, 0.0f, 0.0f);

    entity.AddComponent<Component::IBehaviour, Component::DropBomb>(entity);

    //entity.AddComponent<Prototype::Destructible>(entity, 1);

    return (entity);
}

ECS::Entity& InitButton(ECS::Coordinator& coordinator)
{
    ECS::Entity &entity = coordinator.CreateEntity();
    entity.AddComponent<Component::IUIObject, Component::Button>("../assets/buttons/mapEditorButton.png");
    entity.AddComponent<Component::Transform>(RayLib::Vector3(500.0f, 20.0f, 0.0f), 0.0f, RayLib::Vector3(1.0f, 1.0f, 1.0f));
    entity.AddComponent<Component::IBehaviour, Component::ButtonCallbacks>(entity);

    Component::Button& button = entity.GetComponent<Component::Button>();

    button.AddCallback(std::bind(&Component::ButtonCallbacks::StaticCallback));

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

ECS::Entity& InitCamera(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, Component::Transform& target)
{
    ECS::Entity& entity = coordinator.CreateEntity();

    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 100.0f, 0.0f));
    entity.AddComponent<Component::IBehaviour, Component::Camera>(entity, camera, target.position);

    return (entity);
}

int main(void)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

    //! camera pos and target determined by component
    //! attention le 3e arg: world up est important
    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 0.0f, 0.0f), RayLib::Vector3(), RayLib::Vector3(0.0f, 0.0f, 1.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");
    TerrainGenerator map(2);

    ECS::Entity& cat = InitCat(*coordinator.get());
    //ECS::Entity& button = InitButton(*coordinator.get());
    /*ECS::Entity& box = */InitBox(*coordinator.get(), camera);

    //! uncomment to generate a map
    //Scenes::InitMap(*coordinator.get(), camera, map.getMap(), true);            // ajoute la default map en fond

    Scenes::InitMainMenu(*coordinator.get(), camera, map.getMap());

    //! game manager for drag and drop
    ECS::Entity& gameManager = coordinator->CreateEntity();
    gameManager.AddComponent<Component::IBehaviour, Component::GameConfigurator>();

    // ! uncomment to save generated map
    //gameManager.GetComponent<Component::GameConfigurator>().SaveMap();

    InitCamera(*coordinator.get(), camera, cat.GetComponent<Component::Transform>());

    coordinator->AddSystem<Component::PhysicsSystem>();
    coordinator->AddSystem<Component::RenderSystem>();
    coordinator->AddSystem<Component::BehaviourSystem>();
    coordinator->AddSystem<Component::UISystem>(camera);

    window->SetTargetFPS(60);
    //camera.SetCameraMode(CAMERA_FREE);

    while (!window->WindowShouldClose())
    {
        /*if (coordinator->GetEntities().size() == 0)
            Scenes::scenesCtor[coordinator->getCurrentScene()](*(coordinator.get()), camera);*/
        //camera.Update();

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