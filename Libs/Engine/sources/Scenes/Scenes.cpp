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
#include "Drawable3D.hpp"
#include "TextUI.hpp"
#include "AIMapsGenerator.hpp"
#include "Camera.hpp"

std::map<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>> Scenes::scenesCtor =
    {std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>>("MainMenu", &InitMainMenu),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>>("EditorMenu", &InitEditorMenu),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>>("Editor", &InitEditor),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>>("Game", &InitGame),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>>("LoadingScreen", &InitLoadingScreen),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>>("Pause", &InitPause),
     std::pair<std::string, std::function<void(ECS::Coordinator&, RayLib::Camera3D&)>>("OptionsMenu", &InitOptions),
    };

void Scenes::switchScene(ECS::Coordinator &coordinator, std::string &)
{
    std::string str("LoadingScreen");

    coordinator.setCurrentScene(str);
    //am.setNextScene(nextScene);
    //am.loadAssets(coordinator.getScene(nextScene).GetEntities());
}

void Scenes::InitMap(ECS::Coordinator& coordinator, RayLib::Camera3D&, const bool isEditor, int deepness)
{
    EntityFactory entityFactory(coordinator);
    int players = Engine::GameConfiguration::GetPlayers();
    int enemies = Engine::GameConfiguration::GetIA();
    int currentAI = 1;
    int currentPlayer = 1;
    TerrainGenerator &terrainGeneratorRef = Engine::GameConfiguration::GetTerrainGenerator();
    const std::vector<std::string> &map = terrainGeneratorRef.getMap();

    for (size_t y = 0; y < map.size(); y++) {
        for (size_t x = 0; x < map[y].size(); x++) {
            if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::OWALL)
            || map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::INWALL))
                entityFactory.createWall(RayLib::Vector3(static_cast<float>(x * BOX_SIZE), static_cast<float>(deepness), static_cast<float>(y * BOX_SIZE)));
            else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::WEAKBOX))
                entityFactory.createBox(RayLib::Vector3(static_cast<float>(x * BOX_SIZE), static_cast<float>(deepness), static_cast<float>(y * BOX_SIZE)),
                                                           1, isEditor ? true : false);
            else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::MEDIUMBOX))
                entityFactory.createBox(RayLib::Vector3(static_cast<float>(x * BOX_SIZE), static_cast<float>(deepness), static_cast<float>(y * BOX_SIZE)),
                                                           2, isEditor ? true : false);
            else if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::STRONGBOX))
                entityFactory.createBox(RayLib::Vector3(static_cast<float>(x * BOX_SIZE), static_cast<float>(deepness), static_cast<float>(y * BOX_SIZE)),
                                        3, isEditor ? true : false);



            if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::PLAYER) && currentPlayer <= players) {
                //std::cout << "Spawn player at " << "X " << x << " Y " << y << std::endl;
                Engine::playerkeys& playerKeys = Engine::GameConfiguration::GetPlayerKeys(currentPlayer);
                ECS::Entity& player = entityFactory.createPlayer(playerKeys, currentPlayer);
                player.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), static_cast<float>(deepness), static_cast<float>(y * BOX_SIZE));
                if (coordinator.IsGameRunning())
                    entityFactory.createHUDText(player.GetComponent<Component::PlayerInputs>().GetAController(), currentPlayer);
                currentPlayer++;
                continue;
            }

            if (map[y][x] == static_cast<char>(TerrainGenerator::mapTexture::PLAYER) && currentAI <= enemies) {
                //std::cout << "Spawn AI at " << "X " << x << " Y " << y << std::endl;

                ECS::Entity& ai = entityFactory.createAI();
                ai.GetComponent<Component::Transform>().position = RayLib::Vector3(static_cast<float>(x * BOX_SIZE), 1, static_cast<float>(y * BOX_SIZE));
                currentAI++;
            }
        }
    }
}

void Scenes::InitMainMenu(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    EntityFactory entityFactory(coordinator);

    // init camera component
    entityFactory.createCamera(camera);

    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(0, "");
    RayLib::Vector2<float> scale = window->GetScale();
    RayLib::Vector2<int> size = window->GetSize();

    ECS::Entity& entityTitle = entityFactory.createText("Bomberman", "../assets/pixelplay.png", 200.0f, 4.0f);
    Component::TextUI& text = entityTitle.GetComponent<Component::TextUI>();
    entityTitle.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - (text.MeasureText().x * scale.x / size.x / 2),
                                                                               0.2f, 0.0f);

    ECS::Entity &entityPlay = entityFactory.createButton("../assets/buttons/NewGameBtnStd_texture.png");
    entityPlay.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - 200.0f * scale.x / size.x,
                                                                               0.4f, 0.0f);
    entityPlay.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::StartEditorMenu));


    ECS::Entity &entitySettings = entityFactory.createButton("../assets/buttons/OptionsBtnStd_texture.png");
    entitySettings.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - 200.0f * scale.x / size.x,
                                                                               0.5f, 0.0f);
    entitySettings.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::StartOptionMenu));

    ECS::Entity &entityQuit = entityFactory.createButton("../assets/buttons/QuitGameBtnStd_texture.png");
    entityQuit.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - 200.0f * scale.x / size.x,
                                                                               0.6f, 0.0f);
    entityQuit.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::QuitWindow));
}

void Scenes::InitOptions(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    EntityFactory entityFactory(coordinator);
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(0, "");
    RayLib::Vector2<float> scale = window->GetScale();
    RayLib::Vector2<int> size = window->GetSize();

    entityFactory.createCamera(camera);

    ECS::Entity& fullscreenButton = entityFactory.createButton();
    fullscreenButton.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - 200.0f * scale.x / size.x,
        0.25f - 50.0f * scale.y / size.y, 0.0f);
    fullscreenButton.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::ToggleFullScreen));

    ECS::Entity& mainMenuButt = entityFactory.createButton("../assets/buttons/MainMenuBtnStd_texture.png");
    mainMenuButt.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - 200.0f * scale.x / size.x, 0.5f + 300.0f * scale.y / size.y, -0.0f);
    mainMenuButt.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::ExitGameToMainMenu));
}

void Scenes::InitPause(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    EntityFactory entityFactory(coordinator);
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(0, "");
    RayLib::Vector2<float> scale = window->GetScale();
    RayLib::Vector2<int> size = window->GetSize();

    entityFactory.createCamera(camera);

    ECS::Entity& mainMenuButt = entityFactory.createButton("../assets/buttons/MainMenuBtnStd_texture.png");
    mainMenuButt.SetTag("MainMenuPauseButton");
    mainMenuButt.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - 200.0f * scale.x / size.x, 0.25f + 300.0f * scale.y / size.y, 0.0f);
    mainMenuButt.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::ExitGameToMainMenu));

    ECS::Entity& entityReplay = entityFactory.createButton("../assets/buttons/ReplayBtnStd_texture.png");
    entityReplay.SetTag("ReplayPauseButton");
    entityReplay.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - 200.0f * scale.x / size.x, 0.5f + 150.0f * scale.y / size.y, 0.0f);
    entityReplay.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::Replay));


    ECS::Entity& entityPauseText = entityFactory.createText("Pause", "../assets/pixelplay.png", 200.0f, 4.0f);
    entityPauseText.SetTag("PauseText");
    entityPauseText.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - 200.0f * scale.x / size.x, 0.5f - 300.0f * scale.y / size.y, 0.0f);
}

void Scenes::InitLoadingScreen(ECS::Coordinator& coordinator, RayLib::Camera3D&)
{
    EntityFactory entityFactory(coordinator);

    ECS::Entity &loadingBarBg = entityFactory.createBox(RayLib::Vector3(), 1, false);
    loadingBarBg.GetComponent<Component::Transform>().scale = RayLib::Vector3(15, 1, 2);

    ECS::Entity &loadingBar = entityFactory.createBox(RayLib::Vector3(-3.5f, 0.1f, 0.5f), 1, false);
    loadingBar.GetComponent<Component::Transform>().scale = RayLib::Vector3(4, 1, 1);
    loadingBar.RemoveComponent<Component::Renderer>();
    loadingBar.AddComponent<Component::Renderer>();

    /*ECS::Entity &text = entityFactory.createText();
    text.GetComponent<Component::Transform>().position = RayLib::Vector3(200 + 2, 300 + 2);
    text.GetComponent<Component::Transform>().scale = RayLib::Vector3(20, 6);*/
}

void Scenes::InitNbrPlayers(EntityFactory &entityFactory, std::unique_ptr<RayLib::Window>& window)
{
    RayLib::Vector2<float> scale = window->GetScale();
    RayLib::Vector2<int> size = window->GetSize();

//Player
    ECS::Entity& nbrPlayer = entityFactory.createText("Select number of players", "../assets/pixelplay.png", 50.0f, 4.0f);
    Component::TextUI& nbrPlayerText = nbrPlayer.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> nbrPlayerTextSize = nbrPlayerText.MeasureText();
    nbrPlayer.GetComponent<Component::Transform>().position = RayLib::Vector3(0.25f - (nbrPlayerTextSize.x * scale.x / size.x / 2),
        0.25f - (nbrPlayerTextSize.y * scale.y / size.y) - 180 * scale.y / size.y);

    ECS::Entity& plus = entityFactory.createButton("../assets/buttons/Plus_texture.png");
    plus.GetComponent<Component::Transform>().position = RayLib::Vector3(0.25f + (nbrPlayerTextSize.x * scale.x / size.x / 2) - 50 * scale.x / size.x,
        0.25f + nbrPlayerTextSize.y * scale.y / size.y - 180 * scale.y / size.y, 0.0f);
    plus.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::IncrementPlayerNbr));

    ECS::Entity& minus = entityFactory.createButton("../assets/buttons/Minus_texture.png");
    minus.GetComponent<Component::Transform>().position = RayLib::Vector3(0.25f - (nbrPlayerTextSize.x * scale.x / size.x / 2) - 50 * scale.x / size.x,
        0.25f + nbrPlayerTextSize.y * scale.y / size.y - 180 * scale.y / size.y, 0.0f);
    minus.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::DecrementPlayerNbr));

    ECS::Entity& number = entityFactory.createText(std::to_string(Engine::GameConfiguration::GetPlayers()), "../assets/pixelplay.png", 50.0f, 4.0f);
    number.SetTag("TextPlayerNbr");
    Component::TextUI& numberText = number.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> numberTextSize = numberText.MeasureText();
    number.GetComponent<Component::Transform>().position = RayLib::Vector3(0.25f - (numberTextSize.x * scale.x / size.x / 2),
        0.25f - (numberTextSize.y * scale.y / size.y) - 80 * scale.y / size.y);
//IA
    ECS::Entity& nbrIA = entityFactory.createText("Select number of IA", "../assets/pixelplay.png", 50.0f, 4.0f);
    Component::TextUI& nbrIAText = nbrIA.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> nbrIATextSize = nbrIAText.MeasureText();
    nbrIA.GetComponent<Component::Transform>().position = RayLib::Vector3(0.25f - (nbrIATextSize.x * scale.x / size.x / 2),
        0.25f - (nbrIATextSize.y * scale.y / size.y / 2) + 20 * scale.y / size.y);

    ECS::Entity& plusIA = entityFactory.createButton("../assets/buttons/Plus_texture.png");
    plusIA.GetComponent<Component::Transform>().position = RayLib::Vector3(0.25f+ (nbrIATextSize.x * scale.x / size.x / 2),
        0.25f + nbrIATextSize.y * scale.y / size.y + 20 * scale.y / size.y, 0.0f);
    plusIA.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::IncrementIANbr));

    ECS::Entity& minusIA = entityFactory.createButton("../assets/buttons/Minus_texture.png");
    minusIA.GetComponent<Component::Transform>().position = RayLib::Vector3(0.25f - (nbrIATextSize.x * scale.x / size.x / 2) - 90 * scale.x / size.x,
        0.25f + nbrIATextSize.y * scale.y / size.y + 20 * scale.y / size.y, 0.0f);
    minusIA.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::DecrementIANbr));

    ECS::Entity& numberIA = entityFactory.createText(std::to_string(Engine::GameConfiguration::GetIA()), "../assets/pixelplay.png", 50.0f, 4.0f);
    numberIA.SetTag("TextIANbr");
    Component::TextUI& numberIAText = numberIA.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> numberIATextSize = numberIAText.MeasureText();
    numberIA.GetComponent<Component::Transform>().position = RayLib::Vector3(0.25f - (numberIATextSize.x * scale.x / size.x / 2),
        0.25f - (numberIATextSize.y * scale.y / size.y / 2) + 120 * scale.y / size.y);
}

void Scenes::InitEditorMenu(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    EntityFactory entityFactory(coordinator);
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(0, "");
    RayLib::Vector2<float> scale = window->GetScale();
    RayLib::Vector2<int> size = window->GetSize();

    Scenes::InitNbrPlayers(entityFactory, window);

    entityFactory.createCamera(camera, "../assets/EditorMenu.mp3");

    ECS::Entity& gameManager = coordinator.CreateEntity();
    gameManager.AddComponent<Component::IBehaviour, Component::GameConfigurator>();
// Seed Menu
    ECS::Entity& seed = entityFactory.createText("Enter a seed \nor drop a text file", "assets/pixelplay.png", 50.0f, 4.0f);
    Component::TextUI& seedText = seed.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> seedTextSize = seedText.MeasureText();
    seed.GetComponent<Component::Transform>().position = RayLib::Vector3(0.75f - (seedTextSize.x * scale.x / size.x / 2),
        0.25f - (seedTextSize.y * scale.y / size.y / 2), 0.0f);

    ECS::Entity& enterSeed = entityFactory.createTextBox(std::numeric_limits<int>::digits10, "../assets/pixelplay.png", 50.0f, 4.0f);
    enterSeed.GetComponent<Component::Transform>().position = RayLib::Vector3(0.75f - (seedTextSize.x * scale.x / size.x / 2), 0.25f + seedTextSize.y * scale.y / size.y, 0.0f);
    enterSeed.SetTag("TextSeed");

    ECS::Entity& clearSeed = entityFactory.createButton("../assets/buttons/Switch_texture.png");
    clearSeed.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f * 3 - (seedTextSize.x / 2) + 200, window->GetSize().y / 4.0f + seedTextSize.y - 20, 0.0f);
    clearSeed.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::ClearSeed));

//Basic or Complex Map

    ECS::Entity& mapTypeStatus = entityFactory.createText("BASIC", "../assets/pixelplay.png", 50.0f, 4.0f);
    mapTypeStatus.SetTag("TextMapStatus");
    Component::TextUI& mapTypeStatusText = mapTypeStatus.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> mapTypeStatusTextSize = mapTypeStatusText.MeasureText();
    mapTypeStatus.GetComponent<Component::Transform>().position = RayLib::Vector3(0.25f - (mapTypeStatusTextSize.x * scale.x / size.x / 2),
        0.5f - (mapTypeStatusTextSize.y * scale.y / size.y / 2), 0.0f);

    ECS::Entity& mapType = entityFactory.createButton("../assets/buttons/Switch_texture.png");
    mapType.GetComponent<Component::Transform>().position = RayLib::Vector3(0.25f - (mapTypeStatusTextSize.x * scale.x / size.x / 2),
        0.5f + (mapTypeStatusTextSize.y * scale.y / size.y / 2), 0.0f);
    mapType.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::SwitchMapStatus));

//Save Button

    ECS::Entity& save = entityFactory.createButton("../assets/buttons/Save_texture.png");
    save.GetComponent<Component::Transform>().position = RayLib::Vector3(0.9f - (mapTypeStatusTextSize.x * scale.x / size.x / 2),
        0.9f - mapTypeStatusTextSize.y * scale.y / size.y / 2, 0.0f);
    save.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::SaveMap));

// Map Size Header
    ECS::Entity& mapSize = entityFactory.createText("Select map size", "../assets/pixelplay.png", 50.0f, 4.0f);
    Component::TextUI& mapSizeText = mapSize.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> mapSizeTextSize = mapSizeText.MeasureText();
    mapSize.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - (mapSizeTextSize.x * scale.x / size.x / 2),
        0.45f - (mapSizeTextSize.y * scale.y / size.y / 2), 0.0f);

// Map Size Longueur
    ECS::Entity& mapSizeH = entityFactory.createText("Height", "../assets/pixelplay.png", 50.0f, 4.0f);
    Component::TextUI& mapSizeTextH = mapSizeH.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> mapSizeTextSizeH = mapSizeTextH.MeasureText();
    mapSizeH.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - (mapSizeTextSizeH.x * scale.x / size.x / 2),
        0.5f - (mapSizeTextSizeH.y * scale.y / size.y/ 2), 0.0f);

    ECS::Entity& upH = entityFactory.createButton("../assets/buttons/Plus_texture.png");
    upH.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f + (mapSizeTextSizeH.x * scale.x / size.x / 2) + 100 * scale.x / size.x,
        0.5f + mapSizeTextSizeH.y * scale.y / size.y - 30 * scale.y / size.y, 0.0f);
    upH.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::IncrementMapHeight));

    ECS::Entity& downH = entityFactory.createButton("../assets/buttons/Minus_texture.png");
    downH.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - (mapSizeTextSizeH.x * scale.x / size.x / 2) - 200 * scale.x / size.x,
       0.5f + mapSizeTextSizeH.y * scale.y / size.y - 30 * scale.y / size.y, 0.0f);
    downH.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::DecrementMapHeight));

    ECS::Entity& mapHeight = entityFactory.createText(std::to_string(Engine::GameConfiguration::GetMapSize().y), "../assets/pixelplay.png", 50.0f, 4.0f);
    mapHeight.SetTag("TextMapHeight");
    Component::TextUI& mapHeightText = mapHeight.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> mapHeightTextSize = mapHeightText.MeasureText();
    mapHeight.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - (mapHeightTextSize.x * scale.x / size.x / 2),
        0.5f + mapSizeTextSizeH.y * scale.x / size.x + 30 * scale.y / size.y);

// Map Size Largeur
    ECS::Entity& mapSizeW = entityFactory.createText("Width", "../assets/pixelplay.png", 50.0f, 4.0f);
    Component::TextUI& mapSizeTextW = mapSizeW.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> mapSizeTextSizeW = mapSizeTextW.MeasureText();
    mapSizeW.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - (mapSizeTextSizeW.x * scale.x / size.x / 2),
        0.5f - (mapSizeTextSizeW.y * scale.y / size.y / 2) + 160 * scale.y / size.y);

    ECS::Entity& upW = entityFactory.createButton("../assets/buttons/Plus_texture.png");
    upW.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f + (mapSizeTextSizeW.x * scale.x / size.x / 2) + 100 * scale.x / size.x,
        0.5f + mapSizeTextSizeW.y * scale.y / size.y + 130 * scale.y / size.y, 0.0f);
    upW.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::IncrementMapWidth));

    ECS::Entity& downW = entityFactory.createButton("../assets/buttons/Minus_texture.png");
    downW.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - (mapSizeTextSizeW.x * scale.x / size.x / 2) - 200 * scale.x / size.x,
        0.5f + mapSizeTextSizeW.y * scale.y / size.y + 130 * scale.y / size.y, 0.0f);
    downW.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::DecrementMapWidth));

    ECS::Entity& mapWidth = entityFactory.createText(std::to_string(Engine::GameConfiguration::GetMapSize().x), "../assets/pixelplay.png", 50.0f, 4.0f);
    mapWidth.SetTag("TextMapWidth");
    Component::TextUI& mapWidthText = mapWidth.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> mapWidthTextSize = mapWidthText.MeasureText();
    mapWidth.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - (mapWidthTextSize.x * scale.x / size.x / 2),
        0.5f + mapSizeTextSizeW.y * scale.y / size.y + 150 * scale.y / size.y, 0.0f);

// Footer
    ECS::Entity& generate = entityFactory.createButton("../assets/buttons/GenerateBtnStd_texture.png");
    generate.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - 200 * scale.x / size.x, 0.8f, 0.0f);
    generate.GetComponent<Component::Button>().AddCallback(std::bind(&Component::ButtonCallbacks::GenerateBackgroundMap));

    ECS::Entity& play = entityFactory.createButton("../assets/buttons/PlayBtnStd_texture.png");
    play.GetComponent<Component::Transform>().position = RayLib::Vector3(0.5f - 200 * scale.x / size.x, 0.8f + 100 * scale.y / size.y, 0.0f);
    play.GetComponent<Component::Button>().AddCallback(std::bind(&Component::ButtonCallbacks::StartGame));
}

void Scenes::InitEditor(ECS::Coordinator& coordinator, RayLib::Camera3D&)
{
    EntityFactory entityFactory(coordinator);

    ECS::Entity &entityAddBox = entityFactory.createButton("../assets/buttons/MapEditorBtn_texture.png");
    entityAddBox.GetComponent<Component::Transform>().position = RayLib::Vector3(0.0f, 0.0f, 0.0f);
}

void Scenes::InitGame(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    EntityFactory entityFactory(coordinator);

    InitMap(coordinator, camera, false);

    // ! here we add the ai maps generator
    std::vector<std::string> cpymap = Engine::GameConfiguration::GetTerrainGenerator().getMap();
    if (!coordinator.HasSystem<AIMapsGenerator>())
        coordinator.AddSystem<AIMapsGenerator>(cpymap);
    // init camera component

    entityFactory.createCamera(camera);

    ECS::Entity& gameManager = coordinator.CreateEntity();
    gameManager.AddComponent<Component::IBehaviour, Component::GameConfigurator>();

    // create a bomb
    ECS::Entity& bomb = coordinator.CreateEntity();
    bomb.SetTag("Bomb");
    bomb.AddComponent<Component::Drawable3D>("../assets/bomb/Bomb_model.iqm", "../assets/bomb/Bomb_texture.png");
    bomb.AddComponent<Component::Transform>(RayLib::Vector3(1000.0f, 100.0f, 0.0f));
    //bomb.Dispose();

    ECS::Entity& entityTitle = entityFactory.createText("Bomberman", "../assets/pixelplay.png", 200.0f, 4.0f);
    entityTitle.GetComponent<Component::Transform>().position = RayLib::Vector3(-1000.0f, -1.0f, 0.0f);
}

void Scenes::InitGameOver(ECS::Coordinator& coordinator, Component::Camera& camera, const std::string &endingMessage)
{
    std::unique_ptr<RayLib::Window>& windowRef = RayLib::Window::GetInstance(0, "");
    EntityFactory entityFactory(coordinator);

    camera.getEntity().GetComponent<Component::Transform>().position.z = -180;

    ECS::Entity& entityTitle = entityFactory.createText(endingMessage, "../assets/pixelplay.png", 200.0f, 4.0f);
    Component::TextUI& text = entityTitle.GetComponent<Component::TextUI>();
    RayLib::Vector3 center = RayLib::Vector3(windowRef->GetSize().x / 2.0f - (text.MeasureText().x / 2.0f),
                                             windowRef->GetSize().y / 2.0f - 350.0f, 0.0f);
    entityTitle.GetComponent<Component::Transform>().position = center;

    ECS::Entity &entityReplay = entityFactory.createButton("../assets/buttons/ReplayBtnStd_texture.png");
    entityReplay.GetComponent<Component::Transform>().position = RayLib::Vector3(windowRef->GetSize().x / 2.0f - 200.0f,
                                                                               windowRef->GetSize().y / 2.0f + 150.0f, 0.0f);
    entityReplay.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::Replay));

    ECS::Entity &entityMainMenu = entityFactory.createButton("../assets/buttons/MainMenuBtnStd_texture.png");
    entityMainMenu.GetComponent<Component::Transform>().position = RayLib::Vector3(windowRef->GetSize().x / 2.0f - 200.0f,
                                                                                   windowRef->GetSize().y / 2.0f + 300.0f, 0.0f);
    entityMainMenu.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::ExitGameToMainMenu));
}
