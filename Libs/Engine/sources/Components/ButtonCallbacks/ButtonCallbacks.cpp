/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** ButtonCallbacks
*/

#include "Window.hpp"
#include "GameConfiguration.hpp"
#include "ButtonCallbacks.hpp"
#include <TextUI.hpp>

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

    void ButtonCallbacks::IncrementPlayerNbr()
    {
        int playerNbr = Engine::GameConfiguration::GetPlayers();
        auto& coordinator = ECS::Coordinator::GetInstance();

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

    //void ButtonCallbacks::IncrementPlayerNbr()
    //{
    //    Storage &storageRef = _entity.GetComponent<Component::Storage>();
    //
    //    try {
    //        storageRef.getVar("_playersNbr") += 1;
    //    } catch (const std::exception &) {
    //    }
    //}

    void ButtonCallbacks::QuitWindow()
    {
        ECS::Coordinator::GetInstance()->CloseWindow = true;
    }

    void ButtonCallbacks::CreateBox()
    {
        std::cout << "createBox" << std::endl;
    }

    void ButtonCallbacks::StartGame()
    {
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        std::string sceneName = "Game";

        coordinator->setCurrentScene(sceneName);
    }

    void ButtonCallbacks::StartEditorMenu()
    {
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        std::string sceneName = "EditorMenu";

        coordinator->setCurrentScene(sceneName);
    }
}