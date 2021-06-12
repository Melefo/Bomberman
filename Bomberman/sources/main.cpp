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
#include "Movement.hpp"
#include "DropBomb.hpp"
#include "Button.hpp"
#include "ButtonCallbacks.hpp"
#include "Draggable.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "SphereCollider.hpp"
#include "GameConfigurator.hpp"
#include "Scenes.hpp"
#include "AssetManager.hpp"
#include "PlayerInputs.hpp"

#include "TerrainGenerator.hpp"

#define BOX_SIZE 10

ECS::Entity& InitCat(ECS::Coordinator& coordinator)
{
    // cat
    ECS::Entity &entity = coordinator.CreateEntity();
    entity.SetTag("Player");
    entity.AddComponent<Component::Transform>(RayLib::Vector3(30, 0, 30));
    entity.AddComponent<Component::PhysicsBody>();
    entity.AddComponent<Component::Renderer>("Player");
    entity.AddComponent<Component::Animator>("Player", "Idle");
    //entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));
    entity.AddComponent<Component::Collider, Component::SphereCollider>(entity, RayLib::Vector3(), 4.0f);

    //entity.AddComponent<Component::IBehaviour, Component::Movement>(entity, 0.5f, RayLib::Input(RayLib::Vector2<int>(KEY_RIGHT, KEY_LEFT),
    //                                                                                                  RayLib::Vector2<int>(KEY_DOWN, KEY_UP)));

    entity.AddComponent<Component::IBehaviour, Component::PlayerInputs>(entity, RayLib::Input(RayLib::Vector2<int>(KEY_RIGHT, KEY_LEFT),
                                                                                                  RayLib::Vector2<int>(KEY_DOWN, KEY_UP)));

    entity.GetComponent<Component::Transform>().rotation = RayLib::Vector3(-90.0f, 0.0f, 0.0f);

    //entity.AddComponent<Component::IBehaviour, Component::DropBomb>(entity);

    //entity.AddComponent<Prototype::Destructible>(entity, 1);

    return (entity);
}

ECS::Entity& InitButton(ECS::Coordinator& coordinator)
{
    ECS::Entity &entity = coordinator.CreateEntity();
    entity.AddComponent<Component::IUIObject, Component::Button>();

    entity.AddComponent<Component::Renderer>("MapEditorBtnStd");
    entity.AddComponent<Component::Transform>(RayLib::Vector3(500.0f, 20.0f, 0.0f), 0.0f, RayLib::Vector3(1.0f, 1.0f, 1.0f));
    entity.AddComponent<Component::IBehaviour, Component::ButtonCallbacks>(entity);

    Component::Button& button = entity.GetComponent<Component::Button>();

    return (entity);
}

ECS::Entity& InitBox(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    ECS::Entity& entity = coordinator.CreateEntity();
    entity.SetTag("Box");
    entity.AddComponent<Component::Transform>();
    //entity.AddComponent<Prototype::PhysicsBody>();
    entity.AddComponent<Component::Renderer>("Box");
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(10.0f, 10.0f, 10.0f);
    entity.GetComponent<Component::Transform>().position = RayLib::Vector3(-20.0f, 0.0f, 0.0f);

    entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));
    entity.AddComponent<Component::IBehaviour, Component::Draggable>(entity, camera);
    entity.AddComponent<Component::Destructible>(entity, 1);

    return (entity);
}

ECS::Entity& InitCamera(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    ECS::Entity& entity = coordinator.CreateEntity();

    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 100.0f, -50.0f));
    entity.AddComponent<Component::IBehaviour, Component::Camera>(entity, camera);

    return (entity);
}

int main(void)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
    std::unique_ptr<AssetManager>& assetManagerRef = AssetManager::GetInstance();

    //! camera pos and target determined by component
    //! attention le 3e arg: world up est important
    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 10.0f, 10.0f), RayLib::Vector3(), RayLib::Vector3(0.0f, 1.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");
    TerrainGenerator map(4);

    // !uncomment to get a speed pickup
    //ECS::Entity& pickup = entityFactory.createPickUp();
    //pickup.GetComponent<Component::Transform>().position = RayLib::Vector3(20.0f, 0.0f, 20.0f);

    //! uncomment to generate a map
    //Scenes::InitMap(*coordinator.get(), camera, map.getMap(), true);            // ajoute la default map en fond

    //! game manager for drag and drop
    //ECS::Entity& gameManager = coordinator->CreateEntity();
    //gameManager.AddComponent<Component::IBehaviour, Component::GameConfigurator>();

    //! uncomment to save generated map
    //gameManager.GetComponent<Component::GameConfigurator>().SaveMap();


    coordinator->AddSystem<Component::PhysicsSystem>();
    coordinator->AddSystem<Component::UISystem>(camera);
    coordinator->AddSystem<Component::RenderSystem>();
    coordinator->AddSystem<Component::BehaviourSystem>();

    window->SetTargetFPS(60);
    assetManagerRef->loadAssets(coordinator->GetEntities());
    while (!window->WindowShouldClose() && !coordinator->CloseWindow)
    {
        if (coordinator->GetEntities().size() == 0) {
            Scenes::scenesCtor[coordinator->getCurrentScene()](*coordinator.get(), camera, map.getMap());
            assetManagerRef->loadAssets(coordinator->GetEntities());
        }

        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);

        camera.BeginMode();

        //assetManagerRef->lock();
        //bool isLoaded = assetManagerRef->getLoadStatus().isReady;
        //assetManagerRef->unlock();
        //if (isLoaded)
        coordinator->Run();
        //else
        //    Display the loading screen scene

        camera.EndMode();
        window->EndDrawing();
    }
    return (0);
}
