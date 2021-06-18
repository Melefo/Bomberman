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
    };

void Scenes::switchScene(ECS::Coordinator &coordinator, std::string &)
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
    EntityFactory entityFactory(coordinator, camera);

    // init camera component
    entityFactory.createCamera();

    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(0, "");

    ECS::Entity& entityTitle = entityFactory.createText("Bomberman", "assets/pixelplay.png", 200.0f, 4.0f);
    Component::TextUI& text = entityTitle.GetComponent<Component::TextUI>();
    entityTitle.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - (text.MeasureText().x / 2.0f),
                                                                               window->GetSize().y / 2.0f - 350.0f, 0.0f);

    ECS::Entity &entityPlay = entityFactory.createButton("../assets/buttons/NewGameBtnStd_texture.png");
    entityPlay.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - 200.0f,
                                                                               window->GetSize().y / 2.0f - 150.0f, 0.0f);
    entityPlay.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::StartEditorMenu));


    ECS::Entity &entitySettings = entityFactory.createButton("../assets/buttons/OptionsBtnStd_texture.png");
    entitySettings.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - 200.0f,
                                                                               window->GetSize().y / 2.0f - 50.0f, 0.0f);

    ECS::Entity &entityQuit = entityFactory.createButton("../assets/buttons/QuitGameBtnStd_texture.png");
    entityQuit.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - 200.0f,
                                                                               window->GetSize().y / 2.0f + 50.0f, 0.0f);
    entityQuit.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::QuitWindow));
}

void Scenes::InitLoadingScreen(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    EntityFactory entityFactory(coordinator, camera);

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
//Player
    ECS::Entity& nbrPlayer = entityFactory.createText("Select number of players", "../assets/pixelplay.png", 50.0f, 4.0f);
    Component::TextUI& nbrPlayerText = nbrPlayer.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> nbrPlayerTextSize = nbrPlayerText.MeasureText();
    nbrPlayer.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f - (nbrPlayerTextSize.x / 2.0f),
        window->GetSize().y / 4.0f - (nbrPlayerTextSize.y / 2) - 180);

    ECS::Entity& plus = entityFactory.createButton("../assets/buttons/Plus_texture.png");
    plus.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f + (nbrPlayerTextSize.x / 2) - 50, window->GetSize().y / 4.0f + nbrPlayerTextSize.y - 180, 0.0f);
    plus.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::IncrementPlayerNbr));

    ECS::Entity& minus = entityFactory.createButton("../assets/buttons/Minus_texture.png");
    minus.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f - (nbrPlayerTextSize.x / 2) - 50, window->GetSize().y / 4.0f + nbrPlayerTextSize.y - 180, 0.0f);
    minus.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::DecrementPlayerNbr));

    ECS::Entity& number = entityFactory.createText(std::to_string(Engine::GameConfiguration::GetPlayers()), "../assets/pixelplay.png", 50.0f, 4.0f);
    number.SetTag("TextPlayerNbr");
    Component::TextUI& numberText = number.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> numberTextSize = numberText.MeasureText();
    number.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f - (numberTextSize.x / 2.0f),
        window->GetSize().y / 4.0f - (numberTextSize.y / 2) + 100 - 180);
//IA
    ECS::Entity& nbrIA = entityFactory.createText("Select number of IA", "../assets/pixelplay.png", 50.0f, 4.0f);
    Component::TextUI& nbrIAText = nbrIA.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> nbrIATextSize = nbrIAText.MeasureText();
    nbrIA.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f - (nbrIATextSize.x / 2.0f),
        window->GetSize().y / 4.0f - (nbrIATextSize.y / 2) + 20);

    ECS::Entity& plusIA = entityFactory.createButton("../assets/buttons/Plus_texture.png");
    plusIA.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f + (nbrIATextSize.x / 2), window->GetSize().y / 4.0f + nbrIATextSize.y + 20, 0.0f);
    plusIA.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::IncrementIANbr));

    ECS::Entity& minusIA = entityFactory.createButton("../assets/buttons/Minus_texture.png");
    minusIA.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f - (nbrIATextSize.x / 2) - 90, window->GetSize().y / 4.0f + nbrIATextSize.y + 20, 0.0f);
    minusIA.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::DecrementIANbr));

    ECS::Entity& numberIA = entityFactory.createText(std::to_string(Engine::GameConfiguration::GetIA()), "../assets/pixelplay.png", 50.0f, 4.0f);
    numberIA.SetTag("TextIANbr");
    Component::TextUI& numberIAText = numberIA.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> numberIATextSize = numberIAText.MeasureText();
    numberIA.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f - (numberIATextSize.x / 2.0f),
        window->GetSize().y / 4.0f - (numberIATextSize.y / 2) + 100 + 20);
}

void Scenes::InitEditorMenu(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    EntityFactory entityFactory(coordinator, camera);
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(0, "");


    Scenes::InitNbrPlayers(entityFactory, window);
// Seed Menu

    entityFactory.createCamera();

    ECS::Entity& seed = entityFactory.createText("Enter a seed \nor drop a XML file", "assets/pixelplay.png", 50.0f, 4.0f);
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

    ECS::Entity& upH = entityFactory.createButton("../assets/buttons/Plus_texture.png");
    upH.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2 + (mapSizeTextSizeH.x / 2) + 100, window->GetSize().y / 2 + mapSizeTextSizeH.y - 30, 0.0f);
    upH.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::IncrementMapHeight));

    ECS::Entity& downH = entityFactory.createButton("../assets/buttons/Minus_texture.png");
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

    ECS::Entity& upW = entityFactory.createButton("../assets/buttons/Plus_texture.png");
    upW.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2 + (mapSizeTextSizeW.x / 2) + 100, window->GetSize().y / 2 + mapSizeTextSizeW.y + 130, 0.0f);
    upW.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::IncrementMapWidth));

    ECS::Entity& downW = entityFactory.createButton("../assets/buttons/Minus_texture.png");
    downW.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2 - (mapSizeTextSizeW.x / 2) - 200, window->GetSize().y / 2 + mapSizeTextSizeW.y + 130, 0.0f);
    downW.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::DecrementMapWidth));

    ECS::Entity& mapWidth = entityFactory.createText(std::to_string(Engine::GameConfiguration::GetMapSize().x), "../assets/pixelplay.png", 50.0f, 4.0f);
    mapWidth.SetTag("TextMapWidth");
    Component::TextUI& mapWidthText = mapWidth.GetComponent<Component::TextUI>();
    RayLib::Vector2<float> mapWidthTextSize = mapWidthText.MeasureText();
    mapWidth.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - (mapWidthTextSize.x / 2.0f),
        window->GetSize().y / 2 + mapSizeTextSizeW.y + 150, 0.0f);

// Footer
    ECS::Entity& generate = entityFactory.createButton("../assets/buttons/GenerateBtnStd_texture.png");
    generate.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - 200, window->GetSize().y / 5.0f * 4, 0.0f);
    generate.GetComponent<Component::Button>().AddCallback(std::bind(&Component::ButtonCallbacks::GenerateBackgroundMap));

    ECS::Entity& play = entityFactory.createButton("../assets/buttons/PlayBtnStd_texture.png");
    play.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 2.0f - 200, window->GetSize().y / 5.0f * 4 + 100, 0.0f);
    play.GetComponent<Component::Button>().AddCallback(std::bind(&Component::ButtonCallbacks::StartGame));

    ECS::Entity& enterSeed = entityFactory.createTextBox(std::numeric_limits<int>::digits10, "assets/pixelplay.png", 50.0f, 4.0f);
    enterSeed.GetComponent<Component::Transform>().position = RayLib::Vector3(window->GetSize().x / 4.0f * 3 - (seedTextSize.x / 2), window->GetSize().y / 4.0f + seedTextSize.y, 0.0f);
}

void Scenes::InitEditor(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    EntityFactory entityFactory(coordinator, camera);

    ECS::Entity &entityAddBox = entityFactory.createButton("../assets/buttons/MapEditorBtn_texture.png");
    entityAddBox.GetComponent<Component::Transform>().position = RayLib::Vector3(0.0f, 0.0f, 0.0f);
}

void Scenes::InitGame(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
{
    //std::unique_ptr<RayLib::Window>& windowRef = RayLib::Window::GetInstance(0, "");
    EntityFactory entityFactory(coordinator, camera);

    InitMap(coordinator, camera, false);

    // ! here we add the ai maps generator
    std::vector<std::string> cpymap = Engine::GameConfiguration::GetTerrainGenerator().getMap();
    if (!coordinator.HasSystem<AIMapsGenerator>())
        coordinator.AddSystem<AIMapsGenerator>(cpymap);
    // init camera component

    entityFactory.createCamera();

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

    ECS::Entity& mainMenuButt = entityFactory.createButton("../assets/buttons/MainMenuBtnStd_texture.png");
    mainMenuButt.SetTag("MainMenuPauseButton");
    mainMenuButt.GetComponent<Component::Transform>().position = RayLib::Vector3(10000.0f, 10000.0f, 10000.0f);
    mainMenuButt.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::ExitGameToMainMenu));

    ECS::Entity& entityReplay = entityFactory.createButton("../assets/buttons/ReplayBtnStd_texture.png");
    entityReplay.SetTag("ReplayPauseButton");
    entityReplay.GetComponent<Component::Transform>().position = RayLib::Vector3(10000.0f, 10000.0f, 10000.0f);
    entityReplay.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::Replay));
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

    ECS::Entity &entityReplay = entityFactory.createButton("../assets/buttons/ReplayBtnStd_texture.png");
    entityReplay.GetComponent<Component::Transform>().position = RayLib::Vector3(windowRef->GetSize().x / 2.0f - 200.0f,
                                                                               windowRef->GetSize().y / 2.0f + 150.0f, 0.0f);
    entityReplay.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::Replay));

    ECS::Entity &entityMainMenu = entityFactory.createButton("../assets/buttons/MainMenuBtnStd_texture.png");
    entityMainMenu.GetComponent<Component::Transform>().position = RayLib::Vector3(windowRef->GetSize().x / 2.0f - 200.0f,
                                                                                   windowRef->GetSize().y / 2.0f + 300.0f, 0.0f);
    entityMainMenu.GetComponent<Component::Button>().AddCallback(std::bind(Component::ButtonCallbacks::ExitGameToMainMenu));
}
