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
                std::ifstream myfile(droppedFiles[0]);

                std::stringstream buffer;
                buffer << myfile.rdbuf();

                std::istringstream iss;
                iss.str(buffer.str());
                myfile.close();

                //std::cout << iss.str() << std::endl;
                std::cout << "Dropped file: " << droppedFiles[0] << std::endl;

                Serialization::EntityLoader::LoadEntities(iss);

                _window->ClearDroppedFiles();
            }
        }

        if (_coordinator->getCurrentScene() == "Game") {
            if (Engine::GameConfiguration::GetGameOver() == false && CheckGameOver()) {
                Engine::GameConfiguration::SetGameOver(true);
                _coordinator->SetGameIsRunning(false);
                _coordinator->GetSystem<Component::PhysicsSystem>().SetStatus(false);
                ResetPlayersAnimations();
                Scenes::InitGameOver(*_coordinator, Camera::GetMainCamera(), _nbrPlayersAlive == 0? "TIE": "YOU WON, CONGRATS!");
                //_coordinator->GetSystem<Component::BehaviourSystem>().ToggleStatus();
            }
        }
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
        std::string tag = "";

        for (auto &entity : entities) {
            if (entity->GetTag().find("PlayerEntity") != std::string::npos)
                remainingPlayers++;
            if (entity->GetTag().find("AI") != std::string::npos)
                remainingPlayers++;
        }
        _nbrPlayersAlive = remainingPlayers;
        if (_nbrPlayersAlive <= 1) {
            std::cout << "Game is over! GG!" << std::endl;
            return (true);
        }
        return (false);
    }

    void GameConfigurator::FixedUpdate(ECS::Entity&)
    {

    }

    void GameConfigurator::LateUpdate(double, ECS::Entity&)
    {

    }
}
