/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** Scenes
*/

#include "Camera3D.hpp"
#include "Entity.hpp"
#include "Coordinator.hpp"
#include "IUIObject.hpp"
#include "Transform.hpp"
#include "IBehaviour.hpp"
#include "Button.hpp"
#include "Image.hpp"
#include "ButtonCallbacks.hpp"
#include "Renderer.hpp"
#include "EntityFactory.hpp"
#include "Ray.hpp"
#include "TerrainGenerator.hpp"
#include "Scenes.hpp"
#include "Window.hpp"
#include "Texture.hpp"
#include <string>
#include "GameConfigurator.hpp"
#include "TextUI.hpp"

std::map<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&, const std::vector<std::string>&)>> Scenes::scenesCtor =
    {std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&, const std::vector<std::string>&)>>("MainMenu", &InitMainMenu),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&, const std::vector<std::string>&)>>("EditorMenu", &InitEditorMenu),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&, const std::vector<std::string>&)>>("Editor", &InitEditor),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&, const std::vector<std::string>&)>>("Game", &InitGame),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&, const std::vector<std::string>&)>>("LoadingScreen", &InitLoadingScreen),
    };

void Scenes::switchScene(ECS::Coordinator &coordinator, AssetManager &am, std::string &nextScene)
{
    std::string str("LoadingScreen");

    coordinator.setCurrentScene(str);
    am.setNextScene(nextScene);
    am.loadAssets(coordinator.getScene(nextScene).GetEntities());
}

void Scenes::InitMap(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string> &map, const bool isEditor)
{
    EntityFactory entityFactory(coordinator, camera);
    int players = Engine::GameConfiguration::GetPlayers();
    //int enemies = Engine::GameConfiguration::GetEnemies();
    int currentPlayer = 1;

    for (size_t y = 0; y < map.size(); y++) {
        for (size_t x = 0; x < map[y].size(); x++) {
            if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::OWALL)
            || map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::INWALL)) {
                ECS::Entity& wall = entityFactory.createWall();
                wall.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
            } else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::WEAKBOX)) {
                ECS::Entity& box = entityFactory.createBox(1, isEditor ? true : false);
                box.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
            } else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::MEDIUMBOX)) {
                ECS::Entity& box = entityFactory.createBox(2, isEditor ? true : false);
                box.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
            } else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::STRONGBOX)) {
                ECS::Entity& box = entityFactory.createBox(3, isEditor ? true : false);
                box.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
            }

            if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::PLAYER) && currentPlayer <= players) {
                Engine::playerkeys& playerKeys = Engine::GameConfiguration::GetPlayerKeys(currentPlayer);
                ECS::Entity& player = entityFactory.createPlayer(playerKeys);
                player.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
                currentPlayer++;
            }
        }
    }
}

void Scenes::InitMainMenu(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>&)
{
    EntityFactory entityFactory(coordinator, camera);

    // init camera component
    entityFactory.createCamera();

    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(0, "");

    ECS::Entity& entityTitle = entityFactory.createText("Bomberman", "../assets/pixelplay.png", 200.0f, 4.0f);
    Component::TextUI& text = entityTitle.GetComponent<Component::TextUI>();
    entityTitle.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - (text.MeasureText().x / 2.0f),
                                                                               window->GetSize().y / 2.0f - 350.0f, 0.0f);

    ECS::Entity &entityPlay = entityFactory.createButton("NewGameBtnStd");
    entityPlay.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - 200.0f,
                                                                               window->GetSize().y / 2.0f - 150.0f, 0.0f);
    entityPlay.GetComponent<Component::Button>().AddCallback(std::bind(&Component::ButtonCallbacks::StartGame));



    ECS::Entity &entitySettings = entityFactory.createButton("OptionsBtnStd");
    entitySettings.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - 200.0f,
                                                                               window->GetSize().y / 2.0f - 50.0f, 0.0f);

    ECS::Entity &entityQuit = entityFactory.createButton("QuitGameBtnStd");
    entityQuit.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - 200.0f,
                                                                               window->GetSize().y / 2.0f + 50.0f, 0.0f);
    entityQuit.GetComponent<Component::Button>().AddCallback(std::bind(&Component::ButtonCallbacks::QuitWindow));

    //InitMap(coordinator, camera, defaultMap, 0);            // ajoute la default map en fond

}

void Scenes::InitLoadingScreen(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& defaultMap)
{
    EntityFactory entityFactory(coordinator, camera);

    ECS::Entity &loadingBarBg = entityFactory.createBox(1, false);
    loadingBarBg.GetComponent<Component::Transform>().position = RayLib::Vector3(0, 0, 0);
    loadingBarBg.GetComponent<Component::Transform>().scale = RayLib::Vector3(15, 1, 2);

    ECS::Entity &loadingBar = entityFactory.createBox(1, false);
    loadingBar.GetComponent<Component::Transform>().position = RayLib::Vector3(-3.5f, 0.1f, 0.5f);
    loadingBar.GetComponent<Component::Transform>().scale = RayLib::Vector3(4, 1, 1);
    loadingBar.RemoveComponent<Component::Renderer>();
    loadingBar.AddComponent<Component::Renderer>();

    /*ECS::Entity &text = entityFactory.createText();
    text.GetComponent<Component::Transform>().position = RayLib::Vector3(200 + 2, 300 + 2);
    text.GetComponent<Component::Transform>().scale = RayLib::Vector3(20, 6);*/
    (void)defaultMap;
}

void Scenes::InitEditorMenu(ECS::Coordinator&, RayLib::Camera3D&, const std::vector<std::string>&)
{
}

void Scenes::InitEditor(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& selMap)
{
    EntityFactory entityFactory(coordinator, camera);

    ECS::Entity &entityAddBox = entityFactory.createButton("MapEditorBtn");
    entityAddBox.GetComponent<Component::Transform>().position = RayLib::Vector3(0.0f, 0.0f, 0.0f);
    entityAddBox.GetComponent<Component::Button>().AddCallback(std::bind(&Component::ButtonCallbacks::CreateBox));
    (void)selMap;
}

void Scenes::InitGame(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const std::vector<std::string>& map)
{
    EntityFactory entityFactory(coordinator, camera);

    // init camera component

    //InitMap(coordinator, camera, map, 0);
    InitMap(coordinator, camera, map, false);            // ajoute la default map en fond

    /*ECS::Entity &entityPlayer = *///entityFactory.createPlayer("");
    entityFactory.createCamera();

    ECS::Entity& gameManager = coordinator.CreateEntity();
    gameManager.AddComponent<Component::IBehaviour, Component::GameConfigurator>();
}
