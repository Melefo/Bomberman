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
#include "Scenes.hpp"
#include "Window.hpp"
#include "Texture.hpp"
#include <string>
#include "GameConfigurator.hpp"
#include "ButtonCallbacks.hpp"
#include "PhysicsSystem.hpp"
#include "BehaviourSystem.hpp"
#include "TextUI.hpp"
#include "Camera.hpp"

std::map<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>> Scenes::scenesCtor =
    {std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>>("MainMenu", &InitMainMenu),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>>("EditorMenu", &InitEditorMenu),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>>("Editor", &InitEditor),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>>("Game", &InitGame),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>>("LoadingScreen", &InitLoadingScreen),
    };

void Scenes::switchScene(ECS::Coordinator &coordinator, std::string &nextScene)
{
    std::string str("LoadingScreen");

    coordinator.setCurrentScene(str);
    //am.setNextScene(nextScene);
    //am.loadAssets(coordinator.getScene(nextScene).GetEntities());
}

void Scenes::InitMap(ECS::Coordinator& coordinator, RayLib::Camera3D& camera, const bool isEditor, int deepness)
{
    EntityFactory entityFactory(coordinator, camera);
    int players = Engine::GameConfiguration::GetPlayers();
    //int enemies = Engine::GameConfiguration::GetEnemies();
    int currentPlayer = 1;
    TerrainGenerator &terrainGeneratorRef = Engine::GameConfiguration::GetTerrainGenerator();
    const std::vector<std::string> &map = terrainGeneratorRef.getMap();

    for (size_t y = 0; y < map.size(); y++) {
        for (size_t x = 0; x < map[y].size(); x++) {
            if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::OWALL)
            || map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::INWALL)) {
                ECS::Entity& wall = entityFactory.createWall();
                wall.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), static_cast<float>(deepness), static_cast<float>(y * BOX_SIZE));
            } else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::WEAKBOX)) {
                ECS::Entity& box = entityFactory.createBox(1, isEditor ? true : false);
                box.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), static_cast<float>(deepness), static_cast<float>(y * BOX_SIZE));
            } else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::MEDIUMBOX)) {
                ECS::Entity& box = entityFactory.createBox(2, isEditor ? true : false);
                box.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), static_cast<float>(deepness), static_cast<float>(y * BOX_SIZE));
            } else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::STRONGBOX)) {
                ECS::Entity& box = entityFactory.createBox(3, isEditor ? true : false);
                box.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), static_cast<float>(deepness), static_cast<float>(y * BOX_SIZE));
            }

            if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::PLAYER) && currentPlayer <= players) {
                Engine::playerkeys& playerKeys = Engine::GameConfiguration::GetPlayerKeys(currentPlayer);
                ECS::Entity& player = entityFactory.createPlayer(playerKeys);
                player.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), static_cast<float>(deepness), static_cast<float>(y * BOX_SIZE));
                currentPlayer++;
            }
        }
    }
    
}

void Scenes::InitMainMenu(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
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
    entityPlay.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::StartEditorMenu));


    ECS::Entity &entitySettings = entityFactory.createButton("OptionsBtnStd");
    entitySettings.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - 200.0f,
                                                                               window->GetSize().y / 2.0f - 50.0f, 0.0f);

    ECS::Entity &entityQuit = entityFactory.createButton("QuitGameBtnStd");
    entityQuit.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - 200.0f,
                                                                               window->GetSize().y / 2.0f + 50.0f, 0.0f);
    entityQuit.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::QuitWindow));
}

void Scenes::InitLoadingScreen(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
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
}

void Scenes::InitNbrPlayers(EntityFactory &entityFactory, std::unique_ptr<RayLib::Window>& window)
{
    ECS::Entity& nbrPlayer = entityFactory.createText("Select number of players", "../assets/pixelplay.png", 50.0f, 4.0f);
    Component::TextUI& nbrPlayerText = nbrPlayer.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> nbrPlayerTextSize = nbrPlayerText.MeasureText();
    nbrPlayer.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f - (nbrPlayerTextSize.x / 2.0f),
        window->GetSize().y / 4.0f - (nbrPlayerTextSize.y / 2));

    ECS::Entity& plus = entityFactory.createButton("Plus");
    plus.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f + (nbrPlayerTextSize.x / 2) - 50, window->GetSize().y / 4.0f + nbrPlayerTextSize.y, 0.0f);
    plus.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::IncrementPlayerNbr));

    ECS::Entity& minus = entityFactory.createButton("Minus");
    minus.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f - (nbrPlayerTextSize.x / 2) - 50, window->GetSize().y / 4.0f + nbrPlayerTextSize.y, 0.0f);
    minus.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::DecrementPlayerNbr));

    ECS::Entity& number = entityFactory.createText(std::to_string(Engine::GameConfiguration::GetPlayers()), "../assets/pixelplay.png", 50.0f, 4.0f);
    number.SetTag("TextPlayerNbr");
    Component::TextUI& numberText = number.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> numberTextSize = numberText.MeasureText();
    number.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f - (numberTextSize.x / 2.0f),
        window->GetSize().y / 4.0f - (numberTextSize.y / 2) + 100);
}

void Scenes::InitEditorMenu(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    EntityFactory entityFactory(coordinator, camera);
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(0, "");

    Scenes::InitNbrPlayers(entityFactory, window);
// Seed Menu

    entityFactory.createCamera();

    ECS::Entity& seed = entityFactory.createText("Enter a seed \nor drop a XML file", "../assets/pixelplay.png", 50.0f, 4.0f);
    Component::TextUI& seedText = seed.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> seedTextSize = seedText.MeasureText();
    seed.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f * 3 - (seedTextSize.x / 2.0f),
        window->GetSize().y / 4.0f - (seedTextSize.y / 2.0f), 0.0f);

// Map Size Header
    ECS::Entity& mapSize = entityFactory.createText("Select map size", "../assets/pixelplay.png", 50.0f, 4.0f);
    Component::TextUI& mapSizeText = mapSize.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> mapSizeTextSize = mapSizeText.MeasureText();
    mapSize.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2 - (mapSizeTextSize.x / 2.0f),
        window->GetSize().y / 2 - (mapSizeTextSize.y / 2.0f) - 70, 0.0f);

// Map Size Longueur
    ECS::Entity& mapSizeH = entityFactory.createText("Height", "../assets/pixelplay.png", 50.0f, 4.0f);
    Component::TextUI& mapSizeTextH = mapSizeH.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> mapSizeTextSizeH = mapSizeTextH.MeasureText();
    mapSizeH.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2 - (mapSizeTextSizeH.x / 2.0f),
        window->GetSize().y / 2 - (mapSizeTextSizeH.y / 2.0f) - 15, 0.0f);

    ECS::Entity& upH = entityFactory.createButton("Plus");
    upH.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2 + (mapSizeTextSizeH.x / 2) + 100, window->GetSize().y / 2 + mapSizeTextSizeH.y - 30, 0.0f);
    upH.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::IncrementMapHeight));

    ECS::Entity& downH = entityFactory.createButton("Minus");
    downH.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2 - (mapSizeTextSizeH.x / 2) - 200, window->GetSize().y / 2 + mapSizeTextSizeH.y - 30, 0.0f);
    downH.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::DecrementMapHeight));

    ECS::Entity& mapHeight = entityFactory.createText(std::to_string(Engine::GameConfiguration::GetMapSize().y), "../assets/pixelplay.png", 50.0f, 4.0f);
    mapHeight.SetTag("TextMapHeight");
    Component::TextUI& mapHeightText = mapHeight.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> mapHeightTextSize = mapHeightText.MeasureText();
    mapHeight.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - (mapHeightTextSize.x / 2.0f),
        window->GetSize().y / 2 + mapSizeTextSizeH.y);

// Map Size Largeur
    ECS::Entity& mapSizeW = entityFactory.createText("Width", "../assets/pixelplay.png", 50.0f, 4.0f);
    Component::TextUI& mapSizeTextW = mapSizeW.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> mapSizeTextSizeW = mapSizeTextW.MeasureText();
    mapSizeW.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2 - (mapSizeTextSizeW.x / 2.0f),
        window->GetSize().y / 2 - (mapSizeTextSizeW.y / 2.0f) + 160);

    ECS::Entity& upW = entityFactory.createButton("Plus");
    upW.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2 + (mapSizeTextSizeW.x / 2) + 100, window->GetSize().y / 2 + mapSizeTextSizeW.y + 130, 0.0f);
    upW.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::IncrementMapWidth));

    ECS::Entity& downW = entityFactory.createButton("Minus");
    downW.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2 - (mapSizeTextSizeW.x / 2) - 200, window->GetSize().y / 2 + mapSizeTextSizeW.y + 130, 0.0f);
    downW.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::DecrementMapWidth));

    ECS::Entity& mapWidth = entityFactory.createText(std::to_string(Engine::GameConfiguration::GetMapSize().x), "../assets/pixelplay.png", 50.0f, 4.0f);
    mapWidth.SetTag("TextMapWidth");
    Component::TextUI& mapWidthText = mapWidth.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> mapWidthTextSize = mapWidthText.MeasureText();
    mapWidth.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - (mapWidthTextSize.x / 2.0f),
        window->GetSize().y / 2 + mapSizeTextSizeW.y + 150, 0.0f);

// Footer
    ECS::Entity& generate = entityFactory.createButton("GenerateBtnStd");
    generate.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - 200, window->GetSize().y / 5.0f * 4, 0.0f);
    generate.GetComponent<Component::Button>().AddCallback(std::bind(&Component::ButtonCallbacks::GenerateBackgroundMap));

    ECS::Entity& play = entityFactory.createButton("PlayBtnStd");
    play.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - 200, window->GetSize().y / 5.0f * 4 + 100, 0.0f);
    play.GetComponent<Component::Button>().AddCallback(std::bind(&Component::ButtonCallbacks::StartGame));

    ECS::Entity& enterSeed = entityFactory.createTextBox(std::numeric_limits<int>::digits10, "../assets/pixelplay.png", 50.0f, 4.0f);
    enterSeed.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f * 3 - (seedTextSize.x / 2), window->GetSize().y / 4.0f + seedTextSize.y, 0.0f);
}

void Scenes::InitEditor(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    EntityFactory entityFactory(coordinator, camera);

    ECS::Entity &entityAddBox = entityFactory.createButton("MapEditorBtn");
    entityAddBox.GetComponent<Component::Transform>().position = RayLib::Vector3(0.0f, 0.0f, 0.0f);
}

void Scenes::InitGame(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    EntityFactory entityFactory(coordinator, camera);

    // init camera component

    InitMap(coordinator, camera, false);

    entityFactory.createCamera();

    ECS::Entity& gameManager = coordinator.CreateEntity();
    gameManager.AddComponent<Component::IBehaviour, Component::GameConfigurator>();

    // create a bomb
    ECS::Entity& bomb = coordinator.CreateEntity();
    bomb.SetTag("Bomb");
    bomb.AddComponent<Component::Renderer>("Bomb");
    bomb.AddComponent<Component::Transform>(RayLib::Vector3(1000.0f, 100.0f, 0.0f));
    //bomb.Dispose();

    ECS::Entity& entityTitle = entityFactory.createText("Bomberman", "../assets/pixelplay.png", 200.0f, 4.0f);
    Component::TextUI& text = entityTitle.GetComponent<Component::TextUI>();
    entityTitle.GetComponent<Component::Transform>().position = RayLib::Vector3(-1000.0f, -1.0f, 0.0f);
}

void Scenes::InitGameOver(ECS::Coordinator& coordinator, Component::Camera& camera, const std::string &endingMessage)
{
    std::unique_ptr<RayLib::Window>& windowRef = RayLib::Window::GetInstance(0, "");
    EntityFactory entityFactory(coordinator, camera.camera);

    camera.getEntity().GetComponent<Component::Transform>().position.z = -180;

    ECS::Entity& entityTitle = entityFactory.createText(endingMessage, "../assets/pixelplay.png", 200.0f, 4.0f);
    Component::TextUI& text = entityTitle.GetComponent<Component::TextUI>();
    RayLib::Vector3 center = RayLib::Vector3(windowRef->GetSize().x / 2.0f - (text.MeasureText().x / 2.0f),
                                             windowRef->GetSize().y / 2.0f - 350.0f, 0.0f);
    entityTitle.GetComponent<Component::Transform>().position = center;

    ECS::Entity &entityReplay = entityFactory.createButton("ReplayBtnStd");
    entityReplay.GetComponent<Component::Transform>().position = RayLib::Vector3(windowRef->GetSize().x / 2.0f - 200.0f,
                                                                               windowRef->GetSize().y / 2.0f + 150.0f, 0.0f);
    entityReplay.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::Replay));

    ECS::Entity &entityMainMenu = entityFactory.createButton("MainMenuBtnStd");
    entityMainMenu.GetComponent<Component::Transform>().position = RayLib::Vector3(windowRef->GetSize().x / 2.0f - 200.0f,
                                                                                   windowRef->GetSize().y / 2.0f + 300.0f, 0.0f);
    entityMainMenu.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::ExitGameToMainMenu));
}
