/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** ButtonCallbacks
*/

#include "Window.hpp"
#include "GameConfiguration.hpp"
#include "ButtonCallbacks.hpp"
#include "PhysicsSystem.hpp"
#include "Camera.hpp"
#include "Scenes.hpp"
#include "TextUI.hpp"
#include "TextBox.hpp"
#include <cstdlib>

namespace Component
{
    ButtonCallbacks::ButtonCallbacks(ECS::Entity& attatchedEntity) :
    _entity(attatchedEntity), _button(_entity.GetComponent<Button>())
    {
        // add our callback
        //_button.AddCallback(std::bind(&ButtonCallbacks::QuitWindow, this));
    }

    void ButtonCallbacks::Update(double, ECS::Entity&)
    {
        if (_button.IsMouseOver() && RayLib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT)) {
            _button.OnClick();
        }
    }

    void ButtonCallbacks::FixedUpdate(ECS::Entity&)
    {
    }

    void ButtonCallbacks::LateUpdate(double, ECS::Entity&)
    {
    }

    int ButtonCallbacks::GetSeed(void)
    {
        auto& coordinator = ECS::Coordinator::GetInstance();
        std::string seedText;
        std::string::size_type sz;

        for (auto& entity : coordinator->GetEntities())
        {
            if (entity->GetTag() == "TextSeed" && entity->HasComponent<Component::TextBox>()) {
                seedText = entity->GetComponent<Component::TextBox>().GetValue();
                if (seedText != "")
                    return (std::stoi(seedText, &sz));
            }
        }
        return (-1);
    }

    void ButtonCallbacks::ClearSeed(void)
    {
        auto& coordinator = ECS::Coordinator::GetInstance();
        std::string seedText;

        for (auto& entity : coordinator->GetEntities())
        {
            if (entity->GetTag() == "TextSeed" && entity->HasComponent<Component::TextBox>())
                entity->GetComponent<Component::TextBox>().SetValue("");
        }
    }

    void ButtonCallbacks::GenerateBackgroundMap()
    { 
        std::unique_ptr<ECS::Coordinator>& coordinatorRef = ECS::Coordinator::GetInstance();
        int seed = GetSeed();
        bool cameraExists = true;

        try {
            Component::Camera::GetMainCamera();
        } catch (const std::exception &error) {
            std::cerr << error.what() << std::endl;
            cameraExists = false;
        }
        if (!cameraExists)
            return;                 // TODO: create a new camera
        Component::Camera &cameraRef = Component::Camera::GetMainCamera();
        TerrainGenerator &terrainGeneratorRef = Engine::GameConfiguration::GetTerrainGenerator();

        coordinatorRef->RemoveEntities("Wall");
        coordinatorRef->RemoveEntities("Box");
        coordinatorRef->RemoveEntities("AI");
        coordinatorRef->RemoveEntities("PlayerEntity");
        coordinatorRef->RemoveEntities("PickUp");
        coordinatorRef->RemoveEntities("Bomb");
        coordinatorRef->RemoveEntities("HUD");
        coordinatorRef->RemoveEntities("MapFloor");

        terrainGeneratorRef.clearMap();
        terrainGeneratorRef.setMapSize(Engine::GameConfiguration::GetMapSize());
        terrainGeneratorRef.setPlayersNumber(Engine::GameConfiguration::GetPlayers() + Engine::GameConfiguration::GetIA());
        if (seed != -1) {
            Engine::GameConfiguration::SetSeed(seed);
        } else
            Engine::GameConfiguration::SetSeed(std::rand() % 10000);

        if (Engine::GameConfiguration::GetIsMapBasic())
            terrainGeneratorRef.generateBaseMap(Engine::GameConfiguration::GetSeed());
        else
            terrainGeneratorRef.generateRandomMap(Engine::GameConfiguration::GetSeed());
        terrainGeneratorRef.generateBoxes();
        terrainGeneratorRef.placePlayers();

        Scenes::InitMap(*coordinatorRef, cameraRef.camera, false);
        cameraRef.GetEntity().GetComponent<Component::Transform>().position.z = -200;
    }

    void ButtonCallbacks::TextInterfaceLoader(std::string tagName, int nb)
    {
        auto& coordinator = ECS::Coordinator::GetInstance();

        for (auto& entity : coordinator->GetEntities())
        {
            if (entity->GetTag() != tagName || !entity->HasComponent<Component::TextUI>())
                continue;
            entity->GetComponent<Component::TextUI>().SetString(std::to_string(nb));
        }
    }

    void ButtonCallbacks::TextInterfaceLoader(std::string tagName, std::string str)
    {
        auto& coordinator = ECS::Coordinator::GetInstance();

        for (auto& entity : coordinator->GetEntities())
        {
            if (entity->GetTag() != tagName || !entity->HasComponent<Component::TextUI>())
                continue;
            entity->GetComponent<Component::TextUI>().SetString(str);
        }
    }

    void ButtonCallbacks::IncrementPlayerNbr(void)
    {
        int IA = Engine::GameConfiguration::GetIA();
        int playerNbr = Engine::GameConfiguration::GetPlayers();

        if ((IA + playerNbr + 1) > 8)
            return;
        if (playerNbr >= 3)
            return;
        Engine::GameConfiguration::SetPlayers(playerNbr + 1);
        TextInterfaceLoader("TextPlayerNbr", Engine::GameConfiguration::GetPlayers());
    }

    void ButtonCallbacks::DecrementPlayerNbr(void)
    {
        int playerNbr = Engine::GameConfiguration::GetPlayers();
        int IA = Engine::GameConfiguration::GetIA();

        if (((playerNbr - 1) < 0) || ((IA + playerNbr - 1) < 2))
            return;
        Engine::GameConfiguration::SetPlayers(playerNbr - 1);
        TextInterfaceLoader("TextPlayerNbr", Engine::GameConfiguration::GetPlayers());
    }

    void ButtonCallbacks::IncrementIANbr(void)
    {
        int IA = Engine::GameConfiguration::GetIA();
        int playerNbr = Engine::GameConfiguration::GetPlayers();

        if ((IA + playerNbr + 1) > 8)
            return;
        Engine::GameConfiguration::SetIA(IA + 1);
        TextInterfaceLoader("TextIANbr", Engine::GameConfiguration::GetIA());
    }

    void ButtonCallbacks::DecrementIANbr(void)
    {
        int IA = Engine::GameConfiguration::GetIA();
        int playerNbr = Engine::GameConfiguration::GetPlayers();

        if (((IA - 1) < 0) || ((IA + playerNbr - 1) < 2))
            return;
        Engine::GameConfiguration::SetIA(IA - 1);
        TextInterfaceLoader("TextIANbr", Engine::GameConfiguration::GetIA());
    }

    void ButtonCallbacks::IncrementMapHeight(void)
    {
        RayLib::Vector2<int> mapSize = Engine::GameConfiguration::GetMapSize();

        Engine::GameConfiguration::SetMapSize(mapSize.x, mapSize.y + 2);
        TextInterfaceLoader("TextMapHeight", Engine::GameConfiguration::GetMapSize().y);
    }

    void ButtonCallbacks::DecrementMapHeight(void)
    {
        RayLib::Vector2<int> mapSize = Engine::GameConfiguration::GetMapSize();

        if ((mapSize.y - 2) < 7)
            return;
        Engine::GameConfiguration::SetMapSize(mapSize.x, mapSize.y - 2);
        TextInterfaceLoader("TextMapHeight", Engine::GameConfiguration::GetMapSize().y);
    }

    void ButtonCallbacks::IncrementMapWidth(void)
    {
        RayLib::Vector2<int> mapSize = Engine::GameConfiguration::GetMapSize();

        Engine::GameConfiguration::SetMapSize(mapSize.x + 2, mapSize.y);
        TextInterfaceLoader("TextMapWidth", Engine::GameConfiguration::GetMapSize().x);
    }

    void ButtonCallbacks::DecrementMapWidth(void)
    {
        RayLib::Vector2<int> mapSize = Engine::GameConfiguration::GetMapSize();

        if ((mapSize.x - 2) < 7)
            return;
        Engine::GameConfiguration::SetMapSize(mapSize.x - 2, mapSize.y);
        TextInterfaceLoader("TextMapWidth", Engine::GameConfiguration::GetMapSize().x);
    }

    void ButtonCallbacks::IncrementVolume(void)
    {
        float volume = Engine::GameConfiguration::GetVolume();
        float add = 0.01f;
        RayLib::Input input;

        if (volume >= 1.0f)
            return;
        if (input.IsKeyDown(KEY_LEFT_CONTROL) || input.IsKeyDown(KEY_RIGHT_CONTROL))
            add = 0.05f;
        if (volume + add > 1.0f)
            add = 1.0f - volume;
        Engine::GameConfiguration::SetVolume(volume + add);
        TextInterfaceLoader("TextVolumeNbr", std::to_string(static_cast<int>(Engine::GameConfiguration::GetVolume() * 100)) + "%");
    }

    void ButtonCallbacks::DecrementVolume(void)
    {
        float volume = Engine::GameConfiguration::GetVolume();
        float rem = 0.01f;
        RayLib::Input input;

        if (volume <= 0.0f)
            return;
        if (input.IsKeyDown(KEY_LEFT_CONTROL) || input.IsKeyDown(KEY_RIGHT_CONTROL))
            rem = 0.05f;
        if (volume - rem < 0.0f)
            rem = volume;
        Engine::GameConfiguration::SetVolume(volume - rem);
        TextInterfaceLoader("TextVolumeNbr", std::to_string(static_cast<int>(Engine::GameConfiguration::GetVolume() * 100)) + "%");
    }

    void ButtonCallbacks::QuitWindow(void)
    {
        ECS::Coordinator::GetInstance()->CloseWindow = true;
    }

    void ButtonCallbacks::Continue(void)
    {
        std::unique_ptr<ECS::Coordinator>& coordinatorRef = ECS::Coordinator::GetInstance();
        std::string sceneName = "Game";

        coordinatorRef->setCurrentScene(sceneName);
        coordinatorRef->SetGameIsRunning(true);
        Engine::GameConfiguration::SetGameOver(false);
        coordinatorRef->GetSystem<Component::PhysicsSystem>().SetStatus(true);
    }

    void ButtonCallbacks::Replay(void)
    {
        std::unique_ptr<ECS::Coordinator>& coordinatorRef = ECS::Coordinator::GetInstance();
        std::string sceneName = "Game";

        coordinatorRef->setCurrentScene(sceneName);
        coordinatorRef->RemoveEntities("");

        TerrainGenerator &terrainGeneratorRef = Engine::GameConfiguration::GetTerrainGenerator();
        terrainGeneratorRef.clearMap();
        if (Engine::GameConfiguration::GetIsMapBasic())
            terrainGeneratorRef.generateBaseMap(Engine::GameConfiguration::GetSeed());
        else
            terrainGeneratorRef.generateRandomMap(Engine::GameConfiguration::GetSeed());
        terrainGeneratorRef.generateBoxes();
        terrainGeneratorRef.placePlayers();

        coordinatorRef->SetGameIsRunning(true);
        Engine::GameConfiguration::SetGameOver(false);
        coordinatorRef->GetSystem<Component::PhysicsSystem>().SetStatus(true);
    }

    void ButtonCallbacks::StartGame(void)
    {
        if (Engine::GameConfiguration::GetDroppedMap() == false) {
            TerrainGenerator &terrainGeneratorRef = Engine::GameConfiguration::GetTerrainGenerator();
            if (!terrainGeneratorRef.isGenerated()) {
                Engine::GameConfiguration::SetSeed(std::rand() % 10000);
                terrainGeneratorRef.generateBaseMap(Engine::GameConfiguration::GetSeed());
                terrainGeneratorRef.generateBoxes();
                terrainGeneratorRef.placePlayers();
            }
        }
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        std::string sceneName = "Game";

        coordinator->setCurrentScene(sceneName);
        coordinator->DeleteScene("EditorMenu");

        coordinator->SetGameIsRunning(true);
        coordinator->GetSystem<Component::PhysicsSystem>().SetStatus(true);
    }

    void ButtonCallbacks::StartEditorMenu(void)
    {
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        std::string sceneName = "EditorMenu";

        coordinator->setCurrentScene(sceneName);
        coordinator->SetGameIsRunning(false);
    }

    void ButtonCallbacks::StartOptionMenu(void)
    {
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        coordinator->setCurrentScene("OptionsMenu");
    }

    void ButtonCallbacks::ToggleFullScreen(void)
    {
        RayLib::Window::GetInstance(0, "")->ToggleFullScreen();
    }

    void ButtonCallbacks::ExitGameToMainMenu(void)
    {
        std::unique_ptr<ECS::Coordinator>& coordinatorRef = ECS::Coordinator::GetInstance();
        std::string sceneName = "MainMenu";
        TerrainGenerator &terrainGeneratorRef = Engine::GameConfiguration::GetTerrainGenerator();

        ClearSeed();
        terrainGeneratorRef.SetIsGenerated(false);
        coordinatorRef->RemoveEntities("");
        coordinatorRef->setCurrentScene(sceneName);
        coordinatorRef->SetGameIsRunning(false);
        Engine::GameConfiguration::SetGameOver(false);
        coordinatorRef->DeleteScene("Game");
    }

    void ButtonCallbacks::SwitchMapStatus(void)
    {
        bool isMapBasic = Engine::GameConfiguration::GetIsMapBasic();

        if (isMapBasic) {
            Engine::GameConfiguration::SetIsMapBasic(false);
            TextInterfaceLoader("TextMapStatus", "COMPLEX");
        } else {
            Engine::GameConfiguration::SetIsMapBasic(true);
            TextInterfaceLoader("TextMapStatus", "BASIC");
        }
    }

    void ButtonCallbacks::SaveMap(void)
    {
        //! pour le xml (sans arg)
        //Engine::GameConfiguration::SaveMap();

        //! pour le .txt (arg = path)
        Engine::GameConfiguration::SaveMap("map");
    }
}
