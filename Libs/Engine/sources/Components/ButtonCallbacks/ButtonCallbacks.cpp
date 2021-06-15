/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** ButtonCallbacks
*/

#include "Window.hpp"
#include "GameConfiguration.hpp"
#include "ButtonCallbacks.hpp"
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

        coordinatorRef->RemoveComponents("Wall");
        coordinatorRef->RemoveComponents("Box");
        coordinatorRef->RemoveComponents("Player");
        coordinatorRef->RemoveComponents("PickUp");
        coordinatorRef->RemoveComponents("Bomb");

        terrainGeneratorRef.clearMap();
        terrainGeneratorRef.setPlayersNumber(Engine::GameConfiguration::GetPlayers());
        Engine::GameConfiguration::SetSeed(std::rand() % 10000);

        terrainGeneratorRef.generateRandomMap(Engine::GameConfiguration::GetSeed());         // TODO: get the seed entered by the user and put it here
        terrainGeneratorRef.generateBoxes();
        terrainGeneratorRef.placePlayers();

        Scenes::InitMap(*coordinatorRef, cameraRef.camera, false);
        cameraRef.getEntity().GetComponent<Component::Transform>().position.z = -200;
        //std::size_t centerX = terrainGeneratorRef.getMap()[terrainGeneratorRef.getMap().size() / 2].size() / 2;
        //std::size_t centerY = terrainGeneratorRef.getMap().size() / 2;
    }

    void ButtonCallbacks::IncrementPlayerNbr()
    {
        int playerNbr = Engine::GameConfiguration::GetPlayers();
        auto& coordinator = ECS::Coordinator::GetInstance();

        if (playerNbr >= 8)
            return;
        Engine::GameConfiguration::SetPlayers(playerNbr + 1);
        for (auto& entity : coordinator->GetEntities())
        {
            if (entity->GetTag() != "NumberText" || !entity->HasComponent<Component::TextUI>())
                continue;
            entity->GetComponent<Component::TextUI>().SetString(std::to_string(Engine::GameConfiguration::GetPlayers()));
        }
    }

    void ButtonCallbacks::DecrementPlayerNbr()
    {
        int playerNbr = Engine::GameConfiguration::GetPlayers();
        auto& coordinator = ECS::Coordinator::GetInstance();

        if (playerNbr <= 1)
            return;
        Engine::GameConfiguration::SetPlayers(playerNbr - 1);
        for (auto& entity : coordinator->GetEntities())
        {
            if (entity->GetTag() != "NumberText" || !entity->HasComponent<Component::TextUI>())
                continue;
            entity->GetComponent<Component::TextUI>().SetString(std::to_string(Engine::GameConfiguration::GetPlayers()));
        }
    }

    void ButtonCallbacks::QuitWindow()
    {
        ECS::Coordinator::GetInstance()->CloseWindow = true;
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
    }

    void ButtonCallbacks::StartEditorMenu()
    {
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        std::string sceneName = "EditorMenu";

        coordinator->setCurrentScene(sceneName);
        coordinator->SetGameIsRunning(false);
    }
}
