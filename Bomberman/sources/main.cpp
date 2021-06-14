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
#include "AudioDevice.hpp"

#define BOX_SIZE 10

int main(void)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
    std::unique_ptr<AssetManager>& assetManagerRef = AssetManager::GetInstance();

    //! camera pos and target determined by component
    //! attention le 3e arg: world up est important
    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 10.0f, 10.0f), RayLib::Vector3(), RayLib::Vector3(0.0f, 1.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(1920, 1080), "Bomberman");
    TerrainGenerator map(4);

    RayLib::AudioDevice::InitAudioDevice();

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

    Engine::GameConfiguration::SetPlayers(2);
    RayLib::Input player1Input(RayLib::Vector2<int>(KEY_RIGHT, KEY_LEFT), RayLib::Vector2<int>(KEY_DOWN, KEY_UP));

    Engine::GameConfiguration::SetPlayerKeys(1, player1Input, KEY_ENTER);

    RayLib::Input player2Input;
    Engine::GameConfiguration::SetPlayerKeys(2, player2Input, KEY_X);

    Engine::GameConfiguration::SetDebugMode(true);

    coordinator->AddSystem<Component::PhysicsSystem>();
    coordinator->AddSystem<Component::UISystem>(camera);
    coordinator->AddSystem<Component::RenderSystem>();
    coordinator->AddSystem<Component::BehaviourSystem>();

    window->SetTargetFPS(60);
    window->SetExitKey(KEY_ESCAPE);
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
    RayLib::AudioDevice::CloseAudioDevice();
    return (0);
}
