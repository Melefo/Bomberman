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
        std::string::size_type sz;

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

        terrainGeneratorRef.clearMap();
        terrainGeneratorRef.setMapSize(Engine::GameConfiguration::GetMapSize());         //TOFIX : Resizable Map
        terrainGeneratorRef.setPlayersNumber(Engine::GameConfiguration::GetPlayers());
        if (seed != -1) {
            Engine::GameConfiguration::SetSeed(seed);
        } else
            Engine::GameConfiguration::SetSeed(std::rand() % 10000);

        if (Engine::GameConfiguration::GetIsMapBasic())
            terrainGeneratorRef.generateBaseMap(Engine::GameConfiguration::GetSeed());
        else
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

    void ButtonCallbacks::QuitWindow(void)
    {
        ECS::Coordinator::GetInstance()->CloseWindow = true;
    }

    void ButtonCallbacks::Replay(void)
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

    void ButtonCallbacks::StartGame(void)
    {
        if (Engine::GameConfiguration::GetDroppedMap() == false) {
            TerrainGenerator &terrainGeneratorRef = Engine::GameConfiguration::GetTerrainGenerator();
            if (!terrainGeneratorRef.isGenerated()) {
                terrainGeneratorRef.generateRandomMap(0);
                terrainGeneratorRef.generateBoxes();
                terrainGeneratorRef.placePlayers();
            }
        }
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        std::string sceneName = "Game";

        coordinator->setCurrentScene(sceneName);

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

        coordinatorRef->RemoveEntities("");

        coordinatorRef->setCurrentScene(sceneName);
        coordinatorRef->SetGameIsRunning(false);
        Engine::GameConfiguration::SetGameOver(false);
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
