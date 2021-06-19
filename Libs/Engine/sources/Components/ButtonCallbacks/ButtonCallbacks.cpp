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
#include <TextUI.hpp>
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

    void ButtonCallbacks::GenerateBackgroundMap()
    { 
        std::unique_ptr<ECS::Coordinator>& coordinatorRef = ECS::Coordinator::GetInstance();
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
        terrainGeneratorRef.setMapSize(Engine::GameConfiguration::GetMapSize());         //TOFIX : Resizable Map
        terrainGeneratorRef.setPlayersNumber(Engine::GameConfiguration::GetPlayers() + Engine::GameConfiguration::GetIA());
        Engine::GameConfiguration::SetSeed(std::rand() % 10000);

        terrainGeneratorRef.generateRandomMap(Engine::GameConfiguration::GetSeed());         // TODO: get the seed entered by the user and put it here
        terrainGeneratorRef.generateBoxes();
        terrainGeneratorRef.placePlayers();

        Scenes::InitMap(*coordinatorRef, cameraRef.camera, false);
        cameraRef.getEntity().GetComponent<Component::Transform>().position.z = -200;
        //std::size_t centerX = terrainGeneratorRef.getMap()[terrainGeneratorRef.getMap().size() / 2].size() / 2;
        //std::size_t centerY = terrainGeneratorRef.getMap().size() / 2;
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

    void ButtonCallbacks::IncrementPlayerNbr()
    {
        int IA = Engine::GameConfiguration::GetIA();
        int playerNbr = Engine::GameConfiguration::GetPlayers();

        if ((IA + playerNbr + 1) > 8)
            return;
        Engine::GameConfiguration::SetPlayers(playerNbr + 1);
        TextInterfaceLoader("TextPlayerNbr", Engine::GameConfiguration::GetPlayers());
    }

    void ButtonCallbacks::DecrementPlayerNbr()
    {
        int playerNbr = Engine::GameConfiguration::GetPlayers();
        int IA = Engine::GameConfiguration::GetIA();

        if (((playerNbr - 1) < 0) || ((IA + playerNbr - 1) < 2))
            return;
        Engine::GameConfiguration::SetPlayers(playerNbr - 1);
        TextInterfaceLoader("TextPlayerNbr", Engine::GameConfiguration::GetPlayers());
    }

    void ButtonCallbacks::IncrementIANbr()
    {
        int IA = Engine::GameConfiguration::GetIA();
        int playerNbr = Engine::GameConfiguration::GetPlayers();

        if ((IA + playerNbr + 1) > 8)
            return;
        Engine::GameConfiguration::SetIA(IA + 1);
        TextInterfaceLoader("TextIANbr", Engine::GameConfiguration::GetIA());
    }

    void ButtonCallbacks::DecrementIANbr()
    {
        int IA = Engine::GameConfiguration::GetIA();
        int playerNbr = Engine::GameConfiguration::GetPlayers();

        if (((IA - 1) < 0) || ((IA + playerNbr - 1) < 2))
            return;
        Engine::GameConfiguration::SetIA(IA - 1);
        TextInterfaceLoader("TextIANbr", Engine::GameConfiguration::GetIA());
    }

    void ButtonCallbacks::IncrementMapHeight()
    {
        RayLib::Vector2<int> mapSize = Engine::GameConfiguration::GetMapSize();

        Engine::GameConfiguration::SetMapSize(mapSize.x, mapSize.y + 2);
        TextInterfaceLoader("TextMapHeight", Engine::GameConfiguration::GetMapSize().y);
    }

    void ButtonCallbacks::DecrementMapHeight()
    {
        RayLib::Vector2<int> mapSize = Engine::GameConfiguration::GetMapSize();

        if ((mapSize.y - 2) < 7)
            return;
        Engine::GameConfiguration::SetMapSize(mapSize.x, mapSize.y - 2);
        TextInterfaceLoader("TextMapHeight", Engine::GameConfiguration::GetMapSize().y);
    }

    void ButtonCallbacks::IncrementMapWidth()
    {
        RayLib::Vector2<int> mapSize = Engine::GameConfiguration::GetMapSize();

        Engine::GameConfiguration::SetMapSize(mapSize.x + 2, mapSize.y);
        TextInterfaceLoader("TextMapWidth", Engine::GameConfiguration::GetMapSize().x);
    }

    void ButtonCallbacks::DecrementMapWidth()
    {
        RayLib::Vector2<int> mapSize = Engine::GameConfiguration::GetMapSize();

        if ((mapSize.x - 2) < 7)
            return;
        Engine::GameConfiguration::SetMapSize(mapSize.x - 2, mapSize.y);
        TextInterfaceLoader("TextMapWidth", Engine::GameConfiguration::GetMapSize().x);
    }

    void ButtonCallbacks::QuitWindow()
    {
        ECS::Coordinator::GetInstance()->CloseWindow = true;
    }

    void ButtonCallbacks::Replay()
    {
        std::unique_ptr<ECS::Coordinator>& coordinatorRef = ECS::Coordinator::GetInstance();
        std::string sceneName = "Game";

        coordinatorRef->RemoveEntities("");

        TerrainGenerator &terrainGeneratorRef = Engine::GameConfiguration::GetTerrainGenerator();
        terrainGeneratorRef.clearMap();
        terrainGeneratorRef.generateRandomMap(Engine::GameConfiguration::GetSeed());
        terrainGeneratorRef.generateBoxes();
        terrainGeneratorRef.placePlayers();

        coordinatorRef->setCurrentScene(sceneName);
        coordinatorRef->SetGameIsRunning(true);
        Engine::GameConfiguration::SetGameOver(false);
        coordinatorRef->GetSystem<Component::PhysicsSystem>().SetStatus(true);
    }

    void ButtonCallbacks::StartGame()
    {
        TerrainGenerator &terrainGeneratorRef = Engine::GameConfiguration::GetTerrainGenerator();
        if (!terrainGeneratorRef.isGenerated()) {
            terrainGeneratorRef.generateRandomMap(0);
            terrainGeneratorRef.generateBoxes();
            terrainGeneratorRef.placePlayers();
        }
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        std::string sceneName = "Game";

        coordinator->setCurrentScene(sceneName);
        coordinator->SetGameIsRunning(true);
        coordinator->GetSystem<Component::PhysicsSystem>().SetStatus(true);
    }

    void ButtonCallbacks::StartEditorMenu()
    {
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        std::string sceneName = "EditorMenu";

        coordinator->setCurrentScene(sceneName);
        coordinator->SetGameIsRunning(false);
    }

    void ButtonCallbacks::ExitGameToMainMenu()
    {
        std::unique_ptr<ECS::Coordinator>& coordinatorRef = ECS::Coordinator::GetInstance();
        std::string sceneName = "MainMenu";

        coordinatorRef->RemoveEntities("");

        coordinatorRef->setCurrentScene(sceneName);
        coordinatorRef->SetGameIsRunning(false);
        Engine::GameConfiguration::SetGameOver(false);
    }
}
