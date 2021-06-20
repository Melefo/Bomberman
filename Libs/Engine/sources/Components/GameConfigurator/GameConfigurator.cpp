/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** GameConfigurator
*/

#include "GameConfigurator.hpp"
#include "BehaviourSystem.hpp"
#include "PhysicsSystem.hpp"
#include "Animator.hpp"
#include "Scenes.hpp"

namespace Component
{

    GameConfigurator::GameConfigurator() : 
    _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(), "")), _coordinator(ECS::Coordinator::GetInstance())
    {

    }

    void GameConfigurator::Update(double, ECS::Entity&)
    {
        int count = 0;
        // dans le constructeur

        if (_coordinator->getCurrentScene() == "EditorMenu") {
            // if drag n drop
            if (_window->IsFileDropped())
            {
                std::vector<std::string> droppedFiles = _window->GetDroppedFiles(&count);
                // open file

                if (droppedFiles[0].find(".xml") != std::string::npos) {
                    ParseXMLEntities(droppedFiles[0]);
                }
                if (droppedFiles[0].find(".txt") != std::string::npos) {
                    ParseTerrain(droppedFiles[0]);
                }
                _window->ClearDroppedFiles();
            }
        }

        if (_coordinator->getCurrentScene() == "Game") {
            if (Engine::GameConfiguration::GetGameOver() == false && CheckGameOver()) {
                Engine::GameConfiguration::SetGameOver(true);
                _coordinator->SetGameIsRunning(false);
                _coordinator->GetSystem<Component::PhysicsSystem>().SetStatus(false);
                ResetPlayersAnimations();
                if (_nbrPlayersAlive == 0 && _nbrIAsAlive == 0)
                    Scenes::InitGameOver(*_coordinator, Camera::GetMainCamera(), "TIE");
                else if (_nbrPlayersAlive == 0 && _nbrIAsAlive == 1)
                    Scenes::InitGameOver(*_coordinator, Camera::GetMainCamera(), "YOU LOSE");
                else if (_nbrPlayersAlive == 1 && _nbrIAsAlive == 0)
                    Scenes::InitGameOver(*_coordinator, Camera::GetMainCamera(), "YOU WON, CONGRATS");
                //_coordinator->GetSystem<Component::BehaviourSystem>().ToggleStatus();
            }
        }
    }

    void GameConfigurator::ParseXMLEntities(const std::string& path)
    {
        std::ifstream myfile(path);

        std::stringstream buffer;
        buffer << myfile.rdbuf();

        std::istringstream iss;
        iss.str(buffer.str());
        myfile.close();

                //std::cout << iss.str() << std::endl;
                //std::cout << "Dropped file: " << droppedFiles[0] << std::endl;

        // clear all existing entities

        _coordinator->RemoveEntities("Wall");
        _coordinator->RemoveEntities("Box");
        _coordinator->RemoveEntities("AI");
        _coordinator->RemoveEntities("PlayerEntity");
        _coordinator->RemoveEntities("PickUp");
        _coordinator->RemoveEntities("Bomb");

        Serialization::EntityLoader::LoadEntities(iss);

        Engine::GameConfiguration::SetDroppedMap(true);

    }

    //! gestion d'erreur
    void GameConfigurator::ParseTerrain(const std::string& path)
    {
        std::vector<std::string> lines;
        // loop getline
        std::ifstream infile(path);

        //gameconfiguration get terrain
        Component::Camera &cameraRef = Component::Camera::GetMainCamera();
        TerrainGenerator &terrainGeneratorRef = Engine::GameConfiguration::GetTerrainGenerator();

        std::string line;
        while (std::getline(infile, line)) {
            lines.push_back(line);
        }

        _coordinator->RemoveEntities("Wall");
        _coordinator->RemoveEntities("Box");
        _coordinator->RemoveEntities("AI");
        _coordinator->RemoveEntities("PlayerEntity");
        _coordinator->RemoveEntities("PickUp");
        _coordinator->RemoveEntities("Bomb");
        _coordinator->RemoveEntities("HUD");

        // terrain.clear
        terrainGeneratorRef.clearMap();
        // terrain.setmap (lines)
        terrainGeneratorRef.SetMap(lines);
        Scenes::InitMap(*_coordinator, cameraRef.camera, false);
        cameraRef.GetEntity().GetComponent<Component::Transform>().position.z = -200;
        infile.close();
    }

    void GameConfigurator::ResetPlayersAnimations()
    {
        for (auto &entity : _coordinator->GetEntities()) {
            if (entity->GetTag().find("PlayerEntity") != std::string::npos)
                entity->GetComponent<Component::Animator>().SetState("Idle");
        }
    }

    bool GameConfigurator::CheckGameOver(void)
    {
        const std::list<std::unique_ptr<ECS::Entity>>& entities = _coordinator->GetEntities();
        int remainingPlayers = 0;
        int remainingIAs = 0;
        std::string tag = "";

        for (auto &entity : entities) {
            if (entity->GetTag().find("PlayerEntity") != std::string::npos)
                remainingPlayers++;
            if (entity->GetTag().find("AI") != std::string::npos)
                remainingIAs++;
        }
        _nbrPlayersAlive = remainingPlayers;
        _nbrIAsAlive = remainingIAs;
        if (_nbrPlayersAlive + _nbrIAsAlive <= 1)
            return (true);
        return (false);
    }

    void GameConfigurator::FixedUpdate(ECS::Entity&)
    {

    }

    void GameConfigurator::LateUpdate(double, ECS::Entity&)
    {

    }
}
