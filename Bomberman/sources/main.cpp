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
#include "Movement.hpp"
#include "DropBomb.hpp"
#include "Button.hpp"
#include "ButtonCallbacks.hpp"
#include "Draggable.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "GameConfigurator.hpp"
#include "Scenes.hpp"
#include "PlayerInputs.hpp"
#include "TerrainGenerator.hpp"
#include "AudioDevice.hpp"
#include "Physics2D.hpp"
#include "Image.hpp"
#include "PauseSystem.hpp"

int main(int ac, char **av)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

    //! camera pos and target determined by component
    //! attention le 3e arg: world up est important
    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 10.0f, 10.0f), RayLib::Vector3(), RayLib::Vector3(0.0f, 1.0f, 0.0f));
    RayLib::Window::SetTraceLogLevel(LOG_WARNING);
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(960, 540), "Bomberman");
    RayLib::Vector2<int> maxSize = window->GetMaxSize();
    window->SetSize(RayLib::Vector2<int>(static_cast<int>(maxSize.x / 1.5f), static_cast<int>(maxSize.y / 1.5f)));

    RayLib::AudioDevice::InitAudioDevice();

    Engine::GameConfiguration::SetPlayers(3);

    RayLib::Input player1Input;
    Engine::GameConfiguration::SetPlayerKeys(1, player1Input, KEY_E);

    RayLib::Input player2Input(RayLib::Vector2<int>(KEY_RIGHT, KEY_LEFT), RayLib::Vector2<int>(KEY_DOWN, KEY_UP));
    Engine::GameConfiguration::SetPlayerKeys(2, player2Input, KEY_ENTER);

    RayLib::Input player3Input(RayLib::Vector2<int>(KEY_J, KEY_G), RayLib::Vector2<int>(KEY_H, KEY_Y));
    Engine::GameConfiguration::SetPlayerKeys(3, player3Input, KEY_SPACE);

    if (ac == 2 && std::string(av[1]) == "-d")
        Engine::GameConfiguration::SetDebugMode(true);
    else
        Engine::GameConfiguration::SetDebugMode(false);

    Engine::GameConfiguration::SetIA(2);

    coordinator->AddSystem<Component::PhysicsSystem>();
    coordinator->AddSystem<Component::UISystem>();
    coordinator->AddSystem<Component::RenderSystem>();
    coordinator->AddSystem<Component::BehaviourSystem>();
    coordinator->AddSystem<Component::PauseSystem>();

    window->SetTargetFPS(60);
    window->SetExitKey(KEY_END);
    window->SetIcon(RayLib::Image("../assets/Icon.png"));
    window->SetWindowState(FLAG_WINDOW_RESIZABLE);
    while (!window->WindowShouldClose() && !coordinator->CloseWindow)
    {
        if (coordinator->GetEntities().size() == 0 && Scenes::scenesCtor.find(coordinator->getCurrentScene()) != Scenes::scenesCtor.end())
            Scenes::scenesCtor[coordinator->getCurrentScene()](*coordinator.get(), camera);

        window->BeginDrawing();
        window->ClearBackground(RayLib::Color(20, 20, 20, 255));

        camera.BeginMode();

        coordinator->Run();

        camera.EndMode();
        window->EndDrawing();
    }
    RayLib::AudioDevice::CloseAudioDevice();
    return (0);
}
